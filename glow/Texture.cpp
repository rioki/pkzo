// OpenGL Object Wrapper
// Copyright 2016-2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Texture.h"

#include "glow.h"

namespace glow
{
    GLenum gl_internal_format(ColorMode color, DataType data) noexcept
    {
        using enum ColorMode;
        using enum DataType;

        switch (data)
        {
            case INT8:
                switch (color)
                {
                    case R:
                        return GL_R8I;
                    case RG:
                        return GL_RG8I;
                    case RGB:
                    case BGR:
                        return GL_RGB8I;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA8I;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT;
                    default:
                        fail();
                }
            case UINT8:
                switch (color)
                {
                    case R:
                        return GL_RED;
                    case RG:
                        return GL_RG;
                    case RGB:
                    case BGR:
                        return GL_RGB;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT;
                    default:
                        fail();
                }
            case INT16:
                switch (color)
                {
                    case R:
                        return GL_R16I;
                    case RG:
                        return GL_RG16I;
                    case RGB:
                    case BGR:
                        return GL_RGB16I;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA16I;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT16;
                    default:
                        fail();
                }
            case UINT16:
                switch (color)
                {
                    case R:
                        return GL_R16UI;
                    case RG:
                        return GL_RG16UI;
                    case RGB:
                    case BGR:
                        return GL_RGB16UI;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA16UI;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT16;
                    default:
                        fail();
                }
            case INT32:
                switch (color)
                {
                    case R:
                        return GL_R32I;
                    case RG:
                        return GL_RG32I;
                    case RGB:
                    case BGR:
                        return GL_RGB32I;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA32I;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT32;
                    default:
                        fail();
                }
            case UINT32:
                switch (color)
                {
                    case R:
                        return GL_R32UI;
                    case RG:
                        return GL_RG32UI;
                    case RGB:
                    case BGR:
                        return GL_RGB32UI;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA32UI;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT32;
                    default:
                        fail();
                }
            case FLOAT:
            case DOUBLE:
                switch (color)
                {
                    case R:
                        return GL_R32F;
                    case RG:
                        return GL_RG32F;
                    case RGB:
                    case BGR:
                        return GL_RGB32F;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA32F;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT32F;
                    default:
                        fail();
                }
        default:
            fail();
        }
    }

    GLenum gl_format(ColorMode color) noexcept
    {
        using enum ColorMode;

        switch (color)
        {
            case R:
                return GL_RED;
            case RG:
                return GL_RG;
            case RGB:
                return GL_RGB;
            case BGR:
                return GL_BGR;
            case RGBA:
                return GL_RGBA;
            case BGRA:
                return GL_BGRA;
            case DEPTH:
                return GL_DEPTH_COMPONENT;
            default:
                fail();
                return GL_RGBA;
        }
    }

    GLenum gl_type(DataType data) noexcept
    {
        using enum DataType;

        switch (data)
        {
            case INT8:
                return GL_BYTE;
            case UINT8:
                return GL_UNSIGNED_BYTE;
            case INT16:
                return GL_SHORT;
            case UINT16:
                return GL_UNSIGNED_SHORT;
            case INT32:
                return GL_INT;
            case UINT32:
                return GL_UNSIGNED_INT;
            case FLOAT:
                return GL_FLOAT;
            case DOUBLE:
                return GL_DOUBLE;
            default:
                fail();
        }
    }

    GLenum gl_min_filter(FilterMode filter) noexcept
    {
        using enum FilterMode;

        switch (filter)
        {
            case NEAREST:
                return GL_NEAREST;
            case LINEAR:
                return GL_LINEAR_MIPMAP_LINEAR;
            default:
                fail();
        }
    }

    GLenum gl_mag_filter(FilterMode filter) noexcept
    {
        using enum FilterMode;

        switch (filter)
        {
            case NEAREST:
                return GL_NEAREST;
            case LINEAR:
                return GL_LINEAR;
            default:
                fail();
        }
    }

    GLenum gl_wrap_mode(WrapMode wrap) noexcept
    {
        using enum WrapMode;

        switch (wrap)
        {
            case CLAMP:
                return GL_CLAMP_TO_EDGE;
            case REPEAT:
                return GL_REPEAT;
            case MIRRORED_REPEAT:
                return GL_MIRRORED_REPEAT;
            default:
                fail();
        }
    }

    Texture::Texture()
    {
        glGenTextures(1, &id);
        GLOW_CHECK_ERROR();
    }

    unsigned int Texture::get_id() const noexcept
    {
        return id;
    }

    void Texture::upload(glm::uvec2 size, ColorMode color, DataType data, const void* bits, FilterMode filter, WrapMode wrap)
    {
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter(filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter(filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap_mode(wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap_mode(wrap));

        glTexImage2D(GL_TEXTURE_2D, 0, gl_internal_format(color, data), size.x, size.y, 0, gl_format(color), gl_type(data), bits);

        if (filter == FilterMode::LINEAR)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        GLOW_CHECK_ERROR();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
        GLOW_CHECK_ERROR();
    }

    void Texture::bind(unsigned int slot) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
        GLOW_CHECK_ERROR();
    }

    void Texture::unbind(unsigned int slot) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
        GLOW_CHECK_ERROR();
    }
}
