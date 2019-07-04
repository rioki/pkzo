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
    Image::Image(const std::string& file)
    {
        auto surface = IMG_Load(file.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(surface);
    }

    Image::Image(const std::string& file_xpos, const std::string& file_xneg,
                 const std::string& file_ypos, const std::string& file_yneg,
                 const std::string& file_zpos, const std::string& file_zneg)
    {
        auto xpos = IMG_Load(file_xpos.c_str());
        if (xpos == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(xpos);

        auto xneg = IMG_Load(file_xneg.c_str());
        if (xneg == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(xneg);

        auto ypos = IMG_Load(file_ypos.c_str());
        if (ypos == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(ypos);

        auto yneg = IMG_Load(file_yneg.c_str());
        if (yneg == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(yneg);

        auto zpos = IMG_Load(file_zpos.c_str());
        if (zpos == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(zpos);

        auto zneg = IMG_Load(file_zneg.c_str());
        if (zneg == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(zneg);
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

        auto surface = SDL_CreateRGBSurfaceFrom(cdata, w, h, depth, pitch, rmask, gmask, bmask, amask);
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(surface);
    }

    Image::Image(SDL_Surface* s)
    {
        assert(s != nullptr);
        if (s == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        surfaces.push_back(s);
    }

    Image::~Image()
    {
        assert(!surfaces.empty());
        for (auto surface : surfaces)
        {
            SDL_FreeSurface(surface);
        }
        surfaces.clear();
    }

    glm::uvec2 Image::get_size() const
    {
        assert(!surfaces.empty());
        return glm::uvec2(surfaces[0]->w, surfaces[0]->h);
    }

    ColorType Image::get_color_type() const
    {
        assert(!surfaces.empty());
        switch (surfaces[0]->format->BytesPerPixel)
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
        assert(!surfaces.empty());
        return reinterpret_cast<const unsigned char*>(surfaces[0]->pixels);
    }
}
