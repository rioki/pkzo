// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
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
    auto get_sdl_color_mode(SDL_Surface* surface)
    {
        PKZO_ASSERT(surface != nullptr);
        switch (surface->format->BytesPerPixel)
        {
        case 1:
            return ColorMode::GRAYSCALE;
        case 3:
            return ColorMode::RGB;
        case 4:
            return ColorMode::RGBA;
        default:
            PKZO_THROW(std::logic_error, "Unknown pixel format.");
        }
    }

    Texture::Texture(const fs::path& file)
    {
        surface = IMG_Load(file.string().data());
        if (surface == nullptr)
        {
            PKZO_THROW(std::runtime_error, IMG_GetError());
        }

        size = glm::uvec2(surface->w, surface->h);
        color = get_sdl_color_mode(surface);
    }

    Texture::Texture(glm::uvec2 s, ColorMode c)
    : size(s), color(c) {}

    Texture::Texture(SDL_Surface* s)
    : surface(s)
    {
        if (surface == nullptr)
        {
            PKZO_THROW(std::invalid_argument, "Texture::Texture surface is null.");
        }

        size = glm::uvec2(surface->w, surface->h);
        color = get_sdl_color_mode(surface);
    }

    Texture::~Texture()
    {
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        unload();
    }

    void Texture::resize(glm::uvec2 value)
    {
        if (surface != nullptr)
        {
            PKZO_THROW(std::invalid_argument, "Can not resize surface backed texture");
        }

        size = value;
        unload();
    }

    glm::uvec2 Texture::get_size() const
    {
        return size;
    }

    ColorMode Texture::get_color() const
    {
        return color;
    }

    void Texture::bind(glm::uint s)
    {
        slot = s;
        glActiveTexture(GL_TEXTURE0 + slot);
        if (glid == 0)
        {
            upload();
        }
        else
        {
            PKZO_ASSERT(glid != 0);
            glBindTexture(GL_TEXTURE_2D, glid);
        }
    }

    void Texture::unbind()
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glm::uint Texture::get_handle()
    {
        if (glid == 0)
        {
            upload();
        }
        return glid;
    }

        auto color2format(ColorMode color)
    {
        switch (color)
        {
        case ColorMode::GRAYSCALE_FLOAT:
        case ColorMode::GRAYSCALE:
            return GL_R;
        case ColorMode::RGB_FLOAT:
        case ColorMode::RGB:
            return GL_RGB;
        case ColorMode::RGBA_FLOAT:
        case ColorMode::RGBA:
            return GL_RGBA;
        case ColorMode::DEPTH_FLOAT:
        case ColorMode::DEPTH:
            return GL_DEPTH_COMPONENT;
        default:
            PKZO_ASSERT(false && "invalid color type");
            return 0;
        }
    }

    auto color2intformat(ColorMode color)
    {
        switch (color)
        {
        case ColorMode::GRAYSCALE:
            return GL_R;
        case ColorMode::RGB:
            return GL_RGB;
        case ColorMode::RGBA:
            return GL_RGBA;
        case ColorMode::DEPTH:
            return GL_DEPTH_COMPONENT;
        case ColorMode::GRAYSCALE_FLOAT:
            return GL_R32F;
        case ColorMode::RGB_FLOAT:
            return GL_RGB32F;
        case ColorMode::RGBA_FLOAT:
            return GL_RGBA32F;
        case ColorMode::DEPTH_FLOAT:
            return GL_DEPTH_COMPONENT32F;
        default:
            PKZO_ASSERT(false && "invalid color type");
            return 0;
        }
    }

    auto color2type(ColorMode color)
    {
        switch (color)
        {
        case ColorMode::GRAYSCALE:
        case ColorMode::RGB:
        case ColorMode::RGBA:
        case ColorMode::DEPTH:
            return GL_UNSIGNED_BYTE;
        case ColorMode::GRAYSCALE_FLOAT:
        case ColorMode::RGB_FLOAT:
        case ColorMode::RGBA_FLOAT:
        case ColorMode::DEPTH_FLOAT:
            return GL_FLOAT;
        default:
            PKZO_ASSERT(false && "invalid color type");
            return 0;
        }
    }

    void Texture::upload()
    {
        PKZO_ASSERT(glid == 0);

        glGenTextures(1, &glid);
        PKZO_CHECK_OPENGL(glGetError());

        glBindTexture(GL_TEXTURE_2D, glid);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        auto intformat = color2intformat(color);
        auto format = color2format(color);
        auto gltype = color2type(color);
        void*  data = nullptr;
        if (surface != nullptr)
        {
            data = surface->pixels;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, intformat, size.x, size.y, 0, format, gltype, data);
        PKZO_CHECK_OPENGL(glGetError());

        // TODO glGenerateMipmap(GL_TEXTURE_2D);
        PKZO_CHECK_OPENGL(glGetError());
    }

    void Texture::unload()
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
            PKZO_SOFT_ASSERT(glGetError() == GL_NO_ERROR);
        }
    }
}
