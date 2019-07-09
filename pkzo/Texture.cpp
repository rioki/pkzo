// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Texture.h"

#include <cassert>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <GL/glew.h>
#include <algorithm>

#include "dbg.h"

namespace pkzo
{
    Texture::Texture(const fs::path& file)
    {
        surface = IMG_Load(file.string().data());
        if (surface == nullptr)
        {
            PKZO_THROW(std::runtime_error, IMG_GetError());
        }
    }

    Texture::Texture(SDL_Surface* s)
    : surface(s)
    {
        if (surface == nullptr)
        {
            PKZO_THROW(std::invalid_argument, "Texture::Texture surface is null.");
        }
    }

    Texture::~Texture()
    {
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        if (gl_handle != 0)
        {
            glDeleteTextures(1, &gl_handle);
            gl_handle = 0;
            PKZO_SOFT_ASSERT(glGetError() == GL_NO_ERROR);
        }
    }

    glm::uvec2 Texture::get_size() const
    {
        PKZO_ASSERT(surface != nullptr);
        return glm::uvec2(surface->w, surface->h);
    }

    ColorType Texture::get_color_type() const
    {
        PKZO_ASSERT(surface != nullptr);
        switch (surface->format->BytesPerPixel)
        {
        case 1:
            return ColorType::MONO;
        case 3:
            return ColorType::RGB;
        case 4:
            return ColorType::RGBA;
        default:
            throw std::logic_error("Unknown pixel format.");
        }
    }

    void Texture::bind(glm::uint s)
    {
        slot = s;
        glActiveTexture(GL_TEXTURE0 + slot);
        if (gl_handle == 0)
        {
            upload();
        }
        else
        {
            PKZO_ASSERT(gl_handle != 0);
            glBindTexture(GL_TEXTURE_2D, gl_handle);
        }
    }

    void Texture::unbind()
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLenum color2gl(ColorType type)
    {
        switch (type)
        {
        case ColorType::MONO:
            return GL_ALPHA;
        case ColorType::RGB:
            return GL_RGB;
        case ColorType::RGBA:
            return GL_RGBA;
        case ColorType::DEPTH:
            return GL_DEPTH_COMPONENT;
        default:
            PKZO_ASSERT(false && "invalid color type");
            return 0;
        }
    }

    void Texture::upload()
    {
        PKZO_ASSERT(gl_handle == 0);
        PKZO_ASSERT(surface != nullptr);

        glGenTextures(1, &gl_handle);
        PKZO_ASSERT(glGetError() == GL_NO_ERROR);

        glBindTexture(GL_TEXTURE_2D, gl_handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        GLenum glmode = color2gl(get_color_type());

        glTexImage2D(GL_TEXTURE_2D, 0, glmode, surface->w, surface->h, 0, glmode, GL_UNSIGNED_BYTE, surface->pixels);
        PKZO_ASSERT(glGetError() == GL_NO_ERROR);

        glGenerateMipmap(GL_TEXTURE_2D);
        PKZO_ASSERT(glGetError() == GL_NO_ERROR);
    }
}
