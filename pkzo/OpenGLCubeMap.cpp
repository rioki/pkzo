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

#include "pch.h"

#include "OpenGLCubeMap.h"

#include "debug.h"

namespace pkzo
{
    constexpr auto UPLOAD_SLOT = GL_TEXTURE31;

    // implemented int OpenGLTexture.cpp
    GLenum gl_internal_format(DataType type, ColorMode format);
    GLenum gl_format(ColorMode format);
    GLenum gl_type(DataType type);

    std::shared_ptr<OpenGLCubeMap> OpenGLCubeMap::create(const CreateSpecs& specs)
    {
        return std::make_shared<OpenGLCubeMap>(specs);
    }

    OpenGLCubeMap::OpenGLCubeMap(const CreateSpecs& specs)
    {
        id          = specs.id;
        size        = specs.size;
        color_mode  = specs.color_mode;
        data_type   = specs.data_type;

        glGenTextures(1, &handle);
        glActiveTexture(UPLOAD_SLOT);
        glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

        auto s = size;

        /*for (auto m = 0u; m < specs.miplevels; m++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, m, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);

            s = s / 2u;
        }*/

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, gl_internal_format(data_type, color_mode), s, s, 0, gl_format(color_mode), gl_type(data_type), nullptr);

        if (specs.miplevels > 1)
        {
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    }

    OpenGLCubeMap::~OpenGLCubeMap()
    {
        check(handle != 0u);
        glDeleteTextures(1, &handle);
    }

    std::string OpenGLCubeMap::get_id() const
    {
        return id;
    }

    unsigned int OpenGLCubeMap::get_size() const
    {
        return size;
    }

    DataType OpenGLCubeMap::get_data_type() const
    {
        return data_type;
    }

    ColorMode OpenGLCubeMap::get_color_mode() const
    {
        return color_mode;
    }

    GLuint OpenGLCubeMap::get_handle() const
    {
        return handle;
    }

    void OpenGLCubeMap::bind(int slot)
    {              \
        check(slot >= 0);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
    }
}
