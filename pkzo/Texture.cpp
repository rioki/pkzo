//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

#include "functions.h"

namespace pkzo
{
    Texture::Texture()
    : surface(nullptr), glid(0) {}

    Texture::~Texture()
    {
        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    void Texture::load(const std::string& file)
    {
        init();

        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        surface = IMG_Load(file.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
    }

    unsigned int Texture::get_width() const
    {
        if (surface)
        {
            return surface->w;
        }
        else
        {
            return 0;
        }
    }


    unsigned int Texture::get_height() const
    {
        if (surface)
        {
            return surface->h;
        }
        else
        {
            return 0;
        }
    }

    void Texture::bind(unsigned int slot) const
    {
        if (surface != nullptr)
        {
            if (glid == 0)
            {
                upload();
            }
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, glid);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, glid);
        }
    }

    void Texture::upload() const
    {
        glGenTextures(1, &glid);
        glBindTexture(GL_TEXTURE_2D, glid);

        // TODO mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int mode = 0;
        switch (surface->format->BytesPerPixel)
        {
        case 3:
            mode = GL_RGB;
            break;
        case 4:
            mode = GL_RGBA;
            break;
        default:
            throw std::logic_error("Unknown pixel format.");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    }

    void Texture::release() const
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }
}
