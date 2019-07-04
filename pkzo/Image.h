// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "defines.h"
#include "SDLSentry.h"

struct SDL_Surface;

namespace glow
{
    class Texture;
}

namespace pkzo
{
    enum ColorType
    {
        NOCOLOR,
        MONOCHROME,
        RGB,
        RGBA
    };

    class PKZO_EXPORT Image
    {
    public:

        Image(const std::string& file);

        Image(const std::string& file_xpos, const std::string& file_xneg, 
              const std::string& file_ypos, const std::string& file_yneg,
              const std::string& file_zpos, const std::string& file_zneg);

        Image(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data);

        Image(SDL_Surface* surface);
        
        Image(const Image&) = delete;

        ~Image();

        const Image& operator = (const Image&) = delete;

        glm::uvec2 get_size() const;

        ColorType get_color_type() const;

        const unsigned char* get_data() const;

    private:
        SDLSentry sdl_sentry;

        std::vector<SDL_Surface*>      surfaces;
    };
}

#endif
