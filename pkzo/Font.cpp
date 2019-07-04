// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Font.h"

#include <cassert>
#include <stdexcept>
#include <SDL2/SDL_ttf.h>
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
  

    glm::uvec2 Font::estimate(const std::string& text) const
    {
        assert(font != nullptr);

        int w, h;
        TTF_SizeUTF8(font, text.c_str(), &w, &h);

        return glm::uvec2(w, h);
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
