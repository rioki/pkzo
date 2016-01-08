
#include "Font.h"

#include <SDL_ttf.h>

#include "strex.h"

namespace pkzo
{
    Font::Font()
    : font(nullptr) {}
    
    Font::~Font()
    {
        if (font != nullptr)
        {
            TTF_CloseFont(font);
        }
    }
   
    void Font::load(const std::string& file, unsigned int size)
    {
        if (font != nullptr)
        {
            TTF_CloseFont(font);
        }

        font = TTF_OpenFont(file.c_str(), size);
        if (font == nullptr)
        {
            throw std::runtime_error(TTF_GetError());
        }
    }

    std::tuple<unsigned int, unsigned int> Font::estimate(const std::string& text) const
    {
        int w, h;
        TTF_SizeUTF8(font, text.c_str(), &w, &h);

        return std::make_tuple((unsigned int)w, (unsigned int)h);
    }

    Texture Font::render(const std::string& text) const
    {
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

        Texture texture;
        texture.set_surface(surface);

        return texture;
    }
}
