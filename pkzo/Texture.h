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
    enum class ColorType
    {
        MONO,
        RGB,
        RGBA,
        DEPTH
    };

    class PKZO_EXPORT Texture
    {
    public:

        Texture(const fs::path& file);

        Texture(SDL_Surface* surface);

        Texture(const Texture&) = delete;

        ~Texture();

        const Texture& operator = (const Texture&) = delete;

        glm::uvec2 get_size() const;

        ColorType get_color_type() const;

        void bind(glm::uint slot);

        void unbind();

    private:
        SDL_Surface* surface = nullptr;
        glm::uint gl_handle = 0;
        glm::uint slot = 0;

        void upload();
    };
}

#endif
