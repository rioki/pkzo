// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "OpenGLTexture.h"

#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

namespace pkzo
{
    GLenum gl_internal_format(DataType type, ColorMode format)
    {
        using enum ColorMode;
        using enum DataType;

        switch (type)
        {
            case UNSIGNED_BYTE:
                switch (format)
                {
                    case MONO:
                        return GL_RED;
                    case RGB:
                    case BGR:
                        return GL_RGB;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT24;
                    default:
                        std::unreachable();
                }
            case FLOAT:
                switch (format)
                {
                    case MONO:
                        return GL_R32F;
                    case RGB:
                    case BGR:
                        return GL_RGB32F;
                    case RGBA:
                    case BGRA:
                        return GL_RGBA32F;
                    case DEPTH:
                        return GL_DEPTH_COMPONENT32F;
                    default:
                        std::unreachable();
                }
            default:
                std::unreachable();
        }
    }

    GLenum gl_format(ColorMode format)
    {
        using enum ColorMode;
        switch (format)
        {
            case MONO:
                return GL_RED;
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
                std::unreachable();
        }
    }

    GLenum gl_type(DataType type)
    {
        using enum DataType;
        switch (type)
        {
            case UNSIGNED_BYTE:
                return GL_UNSIGNED_BYTE;
            case FLOAT:
                return GL_FLOAT;
            default:
                std::unreachable();
        }
    }

    GLenum gl_min_filter(TextureFilter filter)
    {
        using enum TextureFilter;
        switch (filter)
        {
            case NEAREST:
                return GL_NEAREST;
            case LINEAR:
                return GL_LINEAR;
            case LINEAR_MIPMAP:
                return GL_LINEAR_MIPMAP_LINEAR;
            default:
                std::unreachable();
        }
    }

    GLenum gl_mag_filter(TextureFilter filter)
    {
        using enum TextureFilter;
        switch (filter)
        {
            case NEAREST:
                return GL_NEAREST;
            case LINEAR:
            case LINEAR_MIPMAP:
                return GL_LINEAR;
            default:
                std::unreachable();
        }
    }

    GLenum gl_clamp_s(Clamp clamp)
    {
        using enum Clamp;
        switch (clamp)
        {
            case NO_CLAMP:
                return GL_REPEAT;
            case CLAMP_HORIZONTAL:
                return GL_CLAMP_TO_EDGE;
            case CLAMP_VERTICAL:
                return GL_REPEAT;
            case CLAMP:
                return GL_CLAMP_TO_EDGE;
            default:
                std::unreachable();
        }
    }

    GLenum gl_clamp_t(Clamp clamp)
    {
        using enum Clamp;
        switch (clamp)
        {
            case NO_CLAMP:
                return GL_REPEAT;
            case CLAMP_HORIZONTAL:
                return GL_REPEAT;
            case CLAMP_VERTICAL:
                return GL_CLAMP_TO_EDGE;
            case CLAMP:
                return GL_CLAMP_TO_EDGE;
            default:
                std::unreachable();
        }
    }

    constexpr auto UPLOAD_SLOT = GL_TEXTURE31;

    std::shared_ptr<OpenGLTexture> OpenGLTexture::create(const CreateSpecs& specs)
    {
        return std::make_shared<OpenGLTexture>(specs);
    }

    std::shared_ptr<OpenGLTexture> OpenGLTexture::create(const glm::vec4& color, const std::string& id )
    {
        return create({
            .id         = id,
            .size       = glm::uvec2(1u),
            .data_type  = DataType::FLOAT,
            .color_mode = ColorMode::RGBA,
            .memory     = glm::value_ptr(color),
            .filter     = TextureFilter::NEAREST,
            .clamp      = Clamp::NO_CLAMP
        });
    }

    OpenGLTexture::OpenGLTexture(const CreateSpecs& specs)
    {
        id          = specs.id;
        size        = specs.size;
        color_mode  = specs.color_mode;
        data_type   = specs.data_type;
        filter      = specs.filter;
        clamp       = specs.clamp;
        auto memory = specs.memory;

        glGenTextures(1, &handle);
        glActiveTexture(UPLOAD_SLOT);
        glBindTexture(GL_TEXTURE_2D, handle);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_internal_format(data_type, color_mode), size.x, size.y, 0, gl_format(color_mode), gl_type(data_type), memory);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter(filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter(filter));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_clamp_s(clamp));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_clamp_t(clamp));

        if (filter == TextureFilter::LINEAR_MIPMAP)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    OpenGLTexture::OpenGLTexture(const std::shared_ptr<Texture>& source)
    : OpenGLTexture({
        .id          = source->get_id(),
        .size        = source->get_size(),
        .data_type   = source->get_data_type(),
        .color_mode  = source->get_color_mode(),
        .memory      = source->get_memory(),
        .filter      = source->get_filter(),
        .clamp       = source->get_clamp()
      })
    {}

    OpenGLTexture::~OpenGLTexture()
    {
        check(handle != 0u);
        glDeleteTextures(1, &handle);
    }

    const std::string& OpenGLTexture::get_id() const
    {
        return id;
    }

    glm::uvec2 OpenGLTexture::get_size() const
    {
        return size;
    }

    ColorMode OpenGLTexture::get_color_mode() const
    {
        return color_mode;
    }

    DataType OpenGLTexture::get_data_type() const
    {
        return data_type;
    }

    const void* OpenGLTexture::get_memory() const
    {
        return nullptr;
    }

    TextureFilter OpenGLTexture::get_filter() const
    {
        return filter;
    }

    Clamp OpenGLTexture::get_clamp() const
    {
        return clamp;
    }

    GLuint OpenGLTexture::get_handle() const
    {
        return handle;
    }

    void OpenGLTexture::bind(int slot)
    {
        check(slot >= 0);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, handle);
    }
}
