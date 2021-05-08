//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils.h"
#include "Texture.h"

#undef min
#undef max

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

namespace pkzo
{
    auto init_ft_library()
    {
        static FT_Library ft_library = nullptr;
        if (ft_library == nullptr)
        {
            auto error = FT_Init_FreeType(&ft_library);
            if (error)
            {
                throw std::runtime_error(fmt::format("Failed to initialize free type: {}", FT_Error_String(error)));
            }
        }
        return ft_library;
    }

    class FontImpl
    {
    public:
        FontImpl(const std::filesystem::path& file, unsigned int size);
        FontImpl(const FontImpl&) = delete;
        ~FontImpl();
        FontImpl& operator = (const FontImpl&) = delete;

        glm::uvec2 estimate(const std::string& text) const;
        std::shared_ptr<Texture> render(const std::string& text) const;

    private:
        FT_Library ft_library = init_ft_library();
        FT_Face    face;

        std::tuple<glm::uvec2, glm::uvec2> estimate_impl(const std::u32string& text) const;
    };

    FontImpl::FontImpl(const std::filesystem::path& file, unsigned int size)
    {
        auto error = FT_New_Face(ft_library, file.u8string().c_str(), 0, &face);
        if (error)
        {
            throw std::runtime_error(fmt::format("Failed to load font {}: {}", file.u8string(), FT_Error_String(error)));
        }

        error = FT_Set_Char_Size(face, 0, size*64, 72, 72);
        if (error)
        {
            throw std::runtime_error(fmt::format("Failed size font {}: {}", file.u8string(), FT_Error_String(error)));
        }
    }

    FontImpl::~FontImpl()
    {

    }

    glm::uvec2 FontImpl::estimate(const std::string& text) const
    {
        auto u32text = utf32(text);
        auto [size, start] = estimate_impl(u32text);
        return size;
    }

    void blit(Texture& target, const glm::uvec2& position, FT_Bitmap bitmap)
    {
        DBG_ASSERT(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
        auto th = target.get_size()[1];
        for (auto i = 0u; i < bitmap.width; i++)
        {
            for (auto j = 0u; j < bitmap.rows; j++)
            {
                auto pixel = bitmap.buffer[i + j * bitmap.pitch];
                auto color = static_cast<float>(pixel) / static_cast<float>(bitmap.num_grays);
                auto p = position + glm::uvec2{i, j};
                p.y = th - p.y;
                target.set_texel(p, glm::vec4(1.0f, 1.0f, 1.0f, color));
            }
        }
    }

    std::shared_ptr<Texture> FontImpl::render(const std::string& text) const
    {
        auto u32text = utf32(text);
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
                DBG_TRACE(__FUNCTION__": %s", FT_Error_String(error));
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

    std::tuple<glm::uvec2, glm::uvec2> FontImpl::estimate_impl(const std::u32string& u32text) const
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
                DBG_TRACE(__FUNCTION__": %s", FT_Error_String(error));
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

        return std::make_tuple(glm::uvec2(max - min), -min);
    }

    Font::Font(const std::filesystem::path& f, unsigned int s)
    : file(f), size(s)
    {
        impl = std::make_unique<FontImpl>(f, s);
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
        DBG_ASSERT(impl);
        return impl->estimate(text);
    }

    std::shared_ptr<Texture> Font::render(const std::string& text) const noexcept
    {
        DBG_ASSERT(impl);
        return impl->render(text);
    }


}
