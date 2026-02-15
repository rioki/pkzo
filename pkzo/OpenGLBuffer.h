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

#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "api.h"

namespace pkzo
{
    class PKZO_EXPORT OpenGLBuffer
    {
    public:
        enum class Usage : GLenum
        {
            STATIC = GL_STATIC_DRAW,
            STREAM = GL_STREAM_DRAW
        };

        enum class Type : GLenum
        {
            ARRAY         = GL_ARRAY_BUFFER,
            ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER
        };

        OpenGLBuffer(Type type, Usage usage);
        ~OpenGLBuffer();

        GLuint get_handle() const;
        Type get_type() const;
        Usage get_usage() const;
        GLsizeiptr get_size() const;
        GLsizeiptr get_capacity() const;

        void upload(GLsizeiptr size, const void* data);

        template<glm::length_t N, typename T, glm::qualifier Q>
        void upload(const std::vector<glm::vec<N, T, Q>>& data);

        void bind();

    private:
        GLuint     handle = 0;
        Type       type;
        Usage      usage;
        GLsizeiptr size     = 0;
        GLsizeiptr capacity = 0;

        OpenGLBuffer(const OpenGLBuffer&) = delete;
        OpenGLBuffer& operator = (const OpenGLBuffer&) = delete;
    };

    template<glm::length_t N, typename T, glm::qualifier Q>
    void OpenGLBuffer::upload(const std::vector<glm::vec<N, T, Q>>& data)
    {
        upload(data.size() * sizeof(glm::vec<N, T, Q>), data.data());
    }
}
