// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Image.h"

#include <cassert>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

namespace pkzo
{
    Image::Image(const fs::path& file)
    {
        surface = IMG_Load(file.string().data());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
    }

    Image::Image(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data)
    {
        if (color_type == NOCOLOR)
        {
            throw std::invalid_argument("Image::create: color_type == NOCOLOR");
        }
        if (data == NULL)
        {
            throw std::invalid_argument("Image::create: data == NULL");
        }

        int bpp = color_type == RGB ? 3 : 4;
        int depth = color_type == RGB ? 24 : 32;
        int pitch = w * bpp;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        int rmask = 0xff000000;
        int gmask = 0x00ff0000;
        int bmask = 0x0000ff00;
        int amask = 0x000000ff;
#else
        int rmask = 0x000000ff;
        int gmask = 0x0000ff00;
        int bmask = 0x00ff0000;
        int amask = 0xff000000;
#endif

        void* cdata = malloc(w*h*bpp); // REVIEW: do we need to free this data?
        memcpy(cdata, data, w*h*bpp);

        surface = SDL_CreateRGBSurfaceFrom(cdata, w, h, depth, pitch, rmask, gmask, bmask, amask);
        if (surface == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Image::Image(SDL_Surface* s)
    : surface(s)
    {
        assert(s != nullptr);
        if (s == nullptr)
        {
            throw std::invalid_argument("Image::Image surface is null.");
        }
    }

    Image::~Image()
    {
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    glm::uvec2 Image::get_size() const
    {
        assert(surface != nullptr);
        return glm::uvec2(surface->w, surface->h);
    }

    ColorType Image::get_color_type() const
    {
        assert(surface != nullptr);
        switch (surface->format->BytesPerPixel)
        {
        case 1:
            return MONOCHROME;
        case 3:
            return RGB;
        case 4:
            return RGBA;
        default:
            throw std::logic_error("Unknown pixel format.");
        }
    }

    const unsigned char* Image::get_data() const
    {
        assert(surface != nullptr);
        return reinterpret_cast<const unsigned char*>(surface->pixels);
    }
}
