//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "Texture.h"

#include <SDL2/SDL_image.h>

namespace pkzo
{
    Texture::Texture(const std::filesystem::path& file)
    {
        surface = IMG_Load(file.string().data());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
        label = file.filename().u8string();
    }

    Texture::Texture(SDL_Surface* s, const std::string& l) noexcept
    : surface(s), label(l)
    {
        assert(surface != nullptr);
    }

    Texture::~Texture()
    {
        assert(surface != nullptr);
        SDL_FreeSurface(surface);

        if (gl_id)
        {
            glDeleteTextures(1, &gl_id);
            gl_id = 0;
            assert(glGetError() == GL_NO_ERROR);
        }
    }

    glm::uvec2 Texture::get_size() const noexcept
    {
        assert(surface != nullptr);
        return {surface->w, surface->h};
    }

    auto bytes2format(uint8_t bytes)
    {
        switch (bytes)
        {
        case 1:
            return GL_R;
        case 2:
            return GL_RG; // this is probably wrong
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            assert(false);
            return 0;
        }
    }

    void Texture::upload()
    {
        assert(gl_id == 0);
        assert(surface != nullptr);

        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_2D, gl_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        GLenum type = bytes2format(surface->format->BytesPerPixel);

        glTexImage2D(GL_TEXTURE_2D, 0, type, surface->w, surface->h, 0, type, GL_UNSIGNED_BYTE, surface->pixels);
        assert(glGetError() == GL_NO_ERROR);

        #ifndef NDEBUG
        glObjectLabel(GL_TEXTURE, gl_id, 0, label.data());
        assert(glGetError() == GL_NO_ERROR);
        #endif
    }

    void Texture::bind(glm::uint slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        if (gl_id == 0)
        {
            upload();
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, gl_id);
            assert(glGetError() == GL_NO_ERROR);
        }
    }
}
