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

#include "OpenGLBuffer.h"

#include <algorithm>

#include "debug.h"

namespace pkzo
{
    OpenGLBuffer::OpenGLBuffer(Type type, Usage usage)
    : type(type), usage(usage)
    {
        glGenBuffers(1, &handle);
    }

    OpenGLBuffer::~OpenGLBuffer()
    {
        glDeleteBuffers(1, &handle);
    }

    GLuint OpenGLBuffer::get_handle() const
    {
        return handle;
    }

    OpenGLBuffer::Type OpenGLBuffer::get_type() const
    {
        return type;
    }

    OpenGLBuffer::Usage OpenGLBuffer::get_usage() const
    {
        return usage;
    }

    GLsizeiptr OpenGLBuffer::get_size() const
    {
        return size;
    }

    GLsizeiptr OpenGLBuffer::get_capacity() const
    {
        return capacity;
    }

    void OpenGLBuffer::upload(GLsizeiptr new_size, const void* data)
    {
        check(data != nullptr || new_size == 0);
        check(usage == Usage::STREAM || (capacity == 0u && usage == Usage::STATIC));

        bind();

        if (new_size > capacity)
        {
            capacity = std::max(new_size, capacity * 2);
            glBufferData(std::to_underlying(type), capacity, nullptr, std::to_underlying(usage));
        }

        if (new_size > 0)
        {
            glBufferSubData(std::to_underlying(type), 0, new_size, data);
        }

        size = new_size;
    }

    void OpenGLBuffer::bind()
    {
        glBindBuffer(std::to_underlying(type), handle);
    }
}
