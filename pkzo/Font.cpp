/*
pkzo

Copyright (c) 2014-2018 Sean Farrell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Font.h"

#include <cassert>
#include <SDL_ttf.h>
#include "Image.h"

namespace pkzo
{
    Font::Font(const std::string& file, unsigned int size)
    {
        font = TTF_OpenFont(file.c_str(), size);
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
  

    rgm::uvec2 Font::estimate(const std::string& text) const
    {
        assert(font != nullptr);

        int w, h;
        TTF_SizeUTF8(font, text.c_str(), &w, &h);

        return rgm::uvec2(w, h);
    }

    std::shared_ptr<Image> Font::render(const std::string& text) const
    {
        assert(font != nullptr);
        
        SDL_Surface* surface = nullptr;

        SDL_Color sdl_color = {0};
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

        return std::make_shared<Image>(surface);
    }
}
