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

#include "Texture.h"

namespace pkzo
{
    std::shared_ptr<Font> Font::load(const std::filesystem::path& file, unsigned int size)
    {
        return std::make_shared<Font>(file, size);
    }

    Font::Font(const std::filesystem::path& f, unsigned int s)
    : file(f), size(s)
    {
        font = TTF_OpenFont(file.u8string().data(), size);
        if (font == nullptr)
        {
            throw std::runtime_error(TTF_GetError());
        }
    }

    Font::~Font()
    {
        assert(font != nullptr);
        TTF_CloseFont(font);
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
        assert(font != nullptr);

        int w, h;
        TTF_SizeUTF8(font, text.c_str(), &w, &h);

        return {w, h};
    }

    std::shared_ptr<Texture> Font::render(const std::string& text) const noexcept
    {
        assert(font != nullptr);

        SDL_Surface* surface = nullptr;

        SDL_Color sdl_color = { 0 };
        sdl_color.r = 255;
        sdl_color.g = 255;
        sdl_color.b = 255;

        if (text.empty())
        {
            surface = TTF_RenderUTF8_Blended(font, " ", sdl_color);
        }
        else
        {
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), sdl_color);
        }

        return std::make_shared<Texture>(surface, text);
    }


}
