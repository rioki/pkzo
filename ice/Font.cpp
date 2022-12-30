// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "Font.h"

#include "utils.h"
#include "strex.h"
#include "Texture.h"

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

namespace ice
{
    const std::string safe_FT_Error_String(FT_Error error_code)
    {
        auto str = FT_Error_String(error_code);
        if (str == nullptr)
        {
            return std::to_string(static_cast<unsigned int>(error_code));
        }
        return str;
    }

    FT_Library Font::init_ft_library()
    {
        static FT_Library ft_library = nullptr;
        if (ft_library == nullptr)
        {
            auto error = FT_Init_FreeType(&ft_library);
            if (error)
            {
                throw std::runtime_error(std::format("Failed to initialize free type: {}", safe_FT_Error_String(error)));
            }
        }
        return ft_library;
    }

    Font::Font(const std::filesystem::path& _file, unsigned int _size)
    : file(_file), size(_size)
    {
        auto error = FT_New_Face(ft_library, file.string().c_str(), 0, &face);
        if (error)
        {
            throw std::runtime_error(std::format("Failed to load font {}: {}", file.string(), safe_FT_Error_String(error)));
        }

        error = FT_Set_Char_Size(face, 0, size*64, 72, 72);
        if (error)
        {
            throw std::runtime_error(std::format("Failed size font {}: {}", file.string(), safe_FT_Error_String(error)));
        }
    }

    Font::~Font() = default;

    const std::filesystem::path& Font::get_file() const noexcept
    {
        return file;
    }

    unsigned int Font::get_size() const noexcept
    {
        return size;
    }

    glm::uvec2 Font::estimate(const std::string& text) const noexcept
    {
        auto u32text = strex::utf32(text);
        auto [size, start] = estimate_impl(u32text);
        return size;
    }

    void blit(Texture& target, const glm::uvec2& position, FT_Bitmap bitmap) noexcept
    {
        assert(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
        auto th = target.get_size()[1];
        for (auto i = 0u; i < bitmap.width; i++)
        {
            for (auto j = 0u; j < bitmap.rows; j++)
            {
                auto pixel = bitmap.buffer[i + j * bitmap.pitch];
                auto color = static_cast<float>(pixel) / static_cast<float>(bitmap.num_grays);
                auto p = position + glm::uvec2{i, j};
                p.y = th - p.y;
                target.set_texel(p, glm::vec4(color));
            }
        }
    }

    std::shared_ptr<Texture> Font::render(const std::string& text) const noexcept
    {
        auto u32text = strex::utf32(text);
        auto [size, start] = estimate_impl(u32text);
        auto texture = std::make_shared<Texture>(size, ColorMode::RGBA, DataType::UINT8, nullptr, text);
        auto pen = start;
        auto use_kerning = FT_HAS_KERNING(face);
        auto prev_index = 0u;
        for (const auto& charcode : u32text)
        {
            auto glyph_index = FT_Get_Char_Index(face, charcode);
            auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
            if (error)
            {
                trace(safe_FT_Error_String(error));
                continue;
            }

            if (use_kerning && prev_index && glyph_index)
            {
                FT_Vector delta;
                FT_Get_Kerning(face, prev_index, glyph_index, FT_KERNING_DEFAULT, &delta);
                pen.x += delta.x >> 6;
            }

            auto pos = pen + glm::uvec2{face->glyph->bitmap_left, -face->glyph->bitmap_top};
            blit(*texture, pos, face->glyph->bitmap);
            pen.x += face->glyph->advance.x >> 6;
            prev_index = glyph_index;
        }

        return texture;
    }

    std::tuple<glm::uvec2, glm::uvec2> Font::estimate_impl(const std::u32string& u32text) const noexcept
    {
        auto pen = glm::ivec2{0, 0};
        auto min = glm::ivec2{0, 0};
        auto max = glm::ivec2{0, 0};
        auto use_kerning = FT_HAS_KERNING(face);
        auto prev_index = 0u;
        for (const auto& charcode : u32text)
        {
            auto glyph_index = FT_Get_Char_Index(face, charcode);
            auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
            if (error)
            {
                trace(safe_FT_Error_String(error));
                continue;
            }

            if (use_kerning && prev_index && glyph_index)
            {
                FT_Vector delta;
                FT_Get_Kerning(face, prev_index, glyph_index, FT_KERNING_DEFAULT, &delta);
                pen.x += delta.x >> 6;
            }

            auto left   = pen.x + face->glyph->bitmap_left;
            auto top    = pen.y - face->glyph->bitmap_top;
            auto right  = left + face->glyph->bitmap.width;
            auto bottom = top + face->glyph->bitmap.rows;

            min = glm::min(min, {left, top});
            max = glm::max(max, {right, bottom});

            pen.x += face->glyph->advance.x >> 6;
            prev_index = glyph_index;
        }

        // padding: OpenGL does not like pixels directly on the boundary
        min -= glm::ivec2(2);
        max += glm::ivec2(2);

        return std::make_tuple(glm::uvec2(max - min), -min);
    }
}
