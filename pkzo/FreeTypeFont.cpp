// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "FreeTypeFont.h"

#include <tinyformat.h>

#include "strconv.h"

// FreeType headers are down here, because the wreck havor with windows.h
#include <ft2build.h>
#include FT_FREETYPE_H

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

namespace pkzo
{
    constexpr auto PADDING = 2;

    // Freetype can return null error strings, in this case
    // Handle it and make sure downstream code has something to print.
    std::string ft_error_string(FT_Error error)
    {
        auto str = FT_Error_String(error);
        if (str == nullptr)
        {
            return "Unknown Error";
        }
        return str;
    }

    auto init_ft_library()
    {
        static FT_Library ft_library = nullptr;
        if (ft_library == nullptr)
        {
            auto error = FT_Init_FreeType(&ft_library);
            if (error)
            {
                throw std::runtime_error(std::format("Failed to initialize free type: {}", ft_error_string(error)));
            }
        }
        return ft_library;
    }

    FT_Library ft_library = init_ft_library();

    FreeTypeFont::FreeTypeFont(const std::filesystem::path& file)
    {
        auto error = FT_New_Face(ft_library, file.string().c_str(), 0, &face);
        if (error)
        {
            throw std::runtime_error(std::format("Failed to load font {}: {}", file.string(), ft_error_string(error)));
        }
    }

    FreeTypeFont::~FreeTypeFont()
    {
        FT_Done_Face(face);
    }

    glm::uvec2 FreeTypeFont::estimate(const std::u8string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        return estimate(strconv::utf32(text), pt_size, dpi);
    }

    glm::uvec2 FreeTypeFont::estimate(const std::u16string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        return estimate(strconv::utf32(text), pt_size, dpi);
    }

    glm::uvec2 FreeTypeFont::estimate(const std::u32string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        auto [size, start] = estimate_impl(text, pt_size, dpi);
        return size;
    }


    std::shared_ptr<Texture> FreeTypeFont::render(const std::u8string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        return render(strconv::utf32(text), pt_size, dpi);
    }

    std::shared_ptr<Texture> FreeTypeFont::render(const std::u16string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        return render(strconv::utf32(text), pt_size, dpi);
    }

    void set_pixel(std::vector<uint8_t>& buffer, glm::uvec2 size, glm::uvec2 position, float color) noexcept
    {
        auto index = (position.x + position.y * size.x) * 4u;
        buffer[index + 0] = 255u;
        buffer[index + 1] = 255u;
        buffer[index + 2] = 255u;
        buffer[index + 3] = static_cast<uint8_t>(color * 255);
    }

    void blit(std::vector<uint8_t>& buffer, glm::uvec2 size, glm::uvec2 position, FT_Bitmap bitmap) noexcept
    {
        assert(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
        for (auto i = 0u; i < bitmap.width; i++)
        {
            for (auto j = 0u; j < bitmap.rows; j++)
            {
                auto pixel = bitmap.buffer[i + j * bitmap.pitch];
                auto color = static_cast<float>(pixel) / static_cast<float>(bitmap.num_grays);
                auto p = position + glm::uvec2{i, j};
                p.y = size.y - p.y;
                set_pixel(buffer, size, p, color);
            }
        }
    }

    std::shared_ptr<Texture> FreeTypeFont::render(const std::u32string_view text, unsigned int pt_size, unsigned int dpi) const
    {
        auto [size, start] = estimate_impl(text, pt_size, dpi);
        auto buffer = std::vector<uint8_t>(size.x * size.y * 4u, 0u);
        auto pen = start;
        auto use_kerning = FT_HAS_KERNING(face);
        auto prev_index = 0u;
        for (const auto& charcode : text)
        {
            auto glyph_index = FT_Get_Char_Index(face, charcode);
            auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
            if (error)
            {
                continue;
            }

            if (use_kerning && prev_index && glyph_index)
            {
                FT_Vector delta;
                FT_Get_Kerning(face, prev_index, glyph_index, FT_KERNING_DEFAULT, &delta);
                pen.x += delta.x >> 6;
            }

            auto pos = pen + glm::uvec2{face->glyph->bitmap_left, -face->glyph->bitmap_top};
            blit(buffer, size, pos, face->glyph->bitmap);
            pen.x += face->glyph->advance.x >> 6;
            prev_index = glyph_index;
        }

        return Texture::create({
            .size       = size,
            .data_type  = DataType::UNSIGNED_BYTE,
            .color_mode = ColorMode::RGBA,
            .memory     = buffer.data(),
            .filter     = TextureFilter::LINEAR
        });
    }

    FontMetrics FreeTypeFont::get_metrics(unsigned int pt_size, unsigned int dpi) const
    {
        auto error = FT_Set_Char_Size(face, 0, pt_size * 64, dpi, dpi);
        if (error)
        {
            throw std::runtime_error(tfm::format("Failed to set font size %dpt @ %ddpi: %s", pt_size, dpi, ft_error_string(error)));
        }

        auto metrics = face->size->metrics;

        return FontMetrics{
            .ascent  = static_cast<int>( metrics.ascender  / 64),
            .descent = static_cast<int>(-metrics.descender / 64),
            .height  = static_cast<int>( metrics.height    / 64)
        };
    }

    std::tuple<glm::uvec2, glm::uvec2> FreeTypeFont::estimate_impl(const std::u32string_view u32text, unsigned int pt_size, unsigned int dpi) const
    {
        auto metrics = get_metrics(pt_size, dpi);

        auto pen = glm::ivec2{0, 0};
        auto min = glm::ivec2{0, -metrics.ascent};
        auto max = glm::ivec2{0, -metrics.descent};
        auto use_kerning = FT_HAS_KERNING(face);
        auto prev_index = 0u;
        for (const auto& charcode : u32text)
        {
            auto glyph_index = FT_Get_Char_Index(face, charcode);
            auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
            if (error)
            {
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
        min -= glm::ivec2(PADDING, PADDING);
        max += glm::ivec2(PADDING, PADDING);

        return std::make_tuple(glm::uvec2(max - min), -min);
    }
}
