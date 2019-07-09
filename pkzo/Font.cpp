// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Font.h"

#include <stdexcept>
#include <SDL2/SDL_ttf.h>
#include "dbg.h"
#include "Texture.h"

namespace pkzo
{
    Font::Font(const fs::path& file, unsigned int size)
    {
        font = TTF_OpenFont(file.string().data(), size);
        if (font == nullptr)
        {
            throw std::runtime_error(TTF_GetError());
        }
    }

    Font::~Font()
    {
        PKZO_ASSERT(font != nullptr);
        TTF_CloseFont(font);
    }

    glm::uvec2 Font::estimate(const std::string& text) const
    {
        PKZO_ASSERT(font != nullptr);

        int w, h;
        TTF_SizeUTF8(font, text.data(), &w, &h);

        return glm::uvec2(w, h);
    }

    std::shared_ptr<Texture> Font::render(const std::string& text) const
    {
        PKZO_ASSERT(font != nullptr);

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
            surface = TTF_RenderUTF8_Blended(font, text.data(), sdl_color);
        }

        return std::make_shared<Texture>(surface);
    }
}
