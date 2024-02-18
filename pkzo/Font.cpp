
// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

namespace pkzo
{
    constexpr auto PADDING = 2u;

    // Freetype can return null error strings, in this case
    // handle it and make sure downstream code has something to print.
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
                throw std::runtime_error(tfm::format("Failed to initialize free type: %s", ft_error_string(error)));
            }
        }
        return ft_library;
    }

    FT_Library ft_library = init_ft_library();

    Font::Font(const std::filesystem::path& f, unsigned int s)
    : file(f), size(s)
    {
        auto error = FT_New_Face(ft_library, file.string().c_str(), 0, &face);
        if (error)
        {
            throw std::runtime_error(std::format("Failed to load font {}: {}", file.string(), ft_error_string(error)));
        }

        error = FT_Set_Char_Size(face, 0, size*64, 72, 72);
        if (error)
        {
            throw std::runtime_error(std::format("Failed size font {}: {}", file.string(), ft_error_string(error)));
        }
    }

    Font::Font(const std::vector<std::byte>& mem, unsigned int s)
    : file("memory"), size(s)
    {
        auto error = FT_New_Memory_Face(ft_library, reinterpret_cast<const FT_Byte*>(mem.data()), static_cast<FT_Long>(mem.size()), 0, &face);
        if (error)
        {
            throw std::runtime_error(std::format("Failed to load font from memory: {}", ft_error_string(error)));
        }

        error = FT_Set_Char_Size(face, 0, size*64, 72, 72);
        if (error)
        {
            throw std::runtime_error(std::format("Failed size font from memory: {}", file.string(), ft_error_string(error)));
        }
    }

    Font::~Font()
    {
        if (face != nullptr)
        {
            FT_Done_Face(face);
        }
    }

    Font::Font(Font&& other) noexcept
    : file(std::move(other.file)), size(other.size), face(other.face)
    {
        other.face = nullptr;
    }

    Font& Font::operator = (Font&& other) noexcept
    {
        std::swap(file, other.file);
        std::swap(size, other.size);
        std::swap(face, other.face);
        return *this;
    }

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
        return estimate(rex::utf32(text));
    }

    glm::uvec2 Font::estimate(const std::wstring& text) const noexcept
    {
        return estimate(rex::utf32(text));
    }

    glm::uvec2 Font::estimate(const std::u8string& text) const noexcept
    {
        return estimate(rex::utf32(text));
    }

    glm::uvec2 Font::estimate(const std::u16string& text) const noexcept
    {
        return estimate(rex::utf32(text));
    }

    glm::uvec2 Font::estimate(const std::u32string& text) const noexcept
    {
        auto [size, start] = estimate_impl(text);
        return size;
    }

    void blit(Image& target, const glm::uvec2& position, FT_Bitmap bitmap) noexcept
    {
        check(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
        auto th = target.get_size()[1];
        for (auto i = 0u; i < bitmap.width; i++)
        {
            for (auto j = 0u; j < bitmap.rows; j++)
            {
                auto pixel = bitmap.buffer[i + j * bitmap.pitch];
                auto color = static_cast<float>(pixel) / static_cast<float>(bitmap.num_grays);
                auto p = position + glm::uvec2{i, j};
                p.y = th - p.y;
                target.set_pixel(p, glm::vec4(color));
            }
        }
    }

    Image Font::render(const std::string& text) const noexcept
    {
        return render(rex::utf32(text));
    }

    Image Font::render(const std::wstring& text) const noexcept
    {
        return render(rex::utf32(text));
    }

    Image Font::render(const std::u8string& text) const noexcept
    {
        return render(rex::utf32(text));
    }

    Image Font::render(const std::u16string& text) const noexcept
    {
        return render(rex::utf32(text));
    }

    Image Font::render(const std::u32string& text) const noexcept
    {
        auto [size, start] = estimate_impl(text);
        auto image = Image(size, ColorMode::RGBA);
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
            blit(image, pos, face->glyph->bitmap);
            pen.x += face->glyph->advance.x >> 6;
            prev_index = glyph_index;
        }

        return image;
    }

    FontMetrics Font::get_metrics() const noexcept
    {
        auto ascent = (static_cast<int>(face->ascender) / (static_cast<int>(face->units_per_EM) / static_cast<int>(size)));
        auto decent = (static_cast<int>(face->descender) / (static_cast<int>(face->units_per_EM) / static_cast<int>(size)));

        return {
            ascent,
            decent,
            (ascent - decent)
        };
    }

    std::tuple<glm::uvec2, glm::uvec2> Font::estimate_impl(const std::u32string& text) const noexcept
    {
        auto metrics = get_metrics();

        auto pen = glm::ivec2{0, 0};
        auto min = glm::ivec2{0, -metrics.ascent};
        auto max = glm::ivec2{0, -metrics.descent};
        auto use_kerning = FT_HAS_KERNING(face);
        auto prev_index = 0u;
        for (const auto& charcode : text)
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
        min -= glm::ivec2(PADDING, 0);
        max += glm::ivec2(PADDING, 0);

        return std::make_tuple(glm::uvec2(max - min), glm::uvec2(-min));
    }
}
