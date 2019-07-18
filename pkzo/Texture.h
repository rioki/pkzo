// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include "defines.h"

#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

#include "stdex.h"
#include "ColorMode.h"

struct SDL_Surface;

namespace fs = std::filesystem;

namespace pkzo
{
    /*!
     * 2D Image
     */
    class PKZO_EXPORT Texture : private stdex::non_copyable
    {
    public:
        /*!
         * Load a texture from file.
         */
        Texture(const fs::path& file);

        /*!
         * Create a memory only texture.
         */
        Texture(glm::uvec2 size, ColorMode color);

        Texture(SDL_Surface* surface);
        ~Texture();

        /*!
         * Resize the texture.
         */
        void resize(glm::uvec2 value);

        glm::uvec2 get_size() const;

        ColorMode get_color() const;

        void bind(glm::uint slot);

        void unbind();

        glm::uint get_handle();

    private:
        glm::uvec2   size    = {0, 0};
        ColorMode    color   = ColorMode::RGB;
        SDL_Surface* surface = nullptr;
        glm::uint    glid    = 0;
        glm::uint    slot    = 0;

        void upload();
        void unload();
    };
}

#endif
