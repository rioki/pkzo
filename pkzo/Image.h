// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

#include "defines.h"

struct SDL_Surface;

namespace fs = std::filesystem;

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

        Image(const fs::path& file);

        Image(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data);

        Image(SDL_Surface* surface);
        
        Image(const Image&) = delete;

        ~Image();

        const Image& operator = (const Image&) = delete;

        glm::uvec2 get_size() const;

        ColorType get_color_type() const;

        const unsigned char* get_data() const;

    private:
        SDL_Surface* surface = nullptr;
    };
}

#endif
