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
#include "VertexBuffer.h"

#include "glow.h"

namespace glow
{
    VertexBuffer::VertexBuffer()
    {
        glGenVertexArrays(1, &vao);
        GLOW_CHECK_ERROR();
    }

    VertexBuffer::~VertexBuffer()
    {
        for (auto& info: buffers)
        {
            if (info.glid != 0)
            {
                glDeleteBuffers(1, &info.glid);
                info.glid = 0;
            }
        }

        for (auto& info: indexes)
        {
            if (info.glid != 0)
            {
                glDeleteBuffers(1, &info.glid);
                info.glid = 0;
            }
        }

        glDeleteVertexArrays(1, &vao);
        vao = 0;

        GLOW_CHECK_ERROR();
    }

    template <typename T>
    unsigned int upload_impl(GLenum type, const std::vector<T>& values) noexcept
    {
        auto glid = 0u;
        glGenBuffers(1, &glid);

        glBindBuffer(type, glid);
        glBufferData(type, values.size() * sizeof(T), values.data(), GL_STATIC_DRAW);

        GLOW_CHECK_ERROR();

        return glid;
    }

    void VertexBuffer::upload_values(const std::string& attrib, const std::vector<glm::vec2>& values) noexcept
    {
        auto glid = upload_impl(GL_ARRAY_BUFFER, values);
        buffers.emplace_back(attrib, 2, values.size(), glid, 0);
    }

    void VertexBuffer::upload_values(const std::string& attrib, const std::vector<glm::vec3>& values) noexcept
    {
        auto glid = upload_impl(GL_ARRAY_BUFFER, values);
        buffers.emplace_back(attrib, 3, values.size(), glid, 0);
    }

    void VertexBuffer::upload_values(const std::string& attrib, const std::vector<glm::vec4>& values) noexcept
    {
        auto glid = upload_impl(GL_ARRAY_BUFFER, values);
        buffers.emplace_back(attrib, 4, values.size(), glid, 0);
    }

    void VertexBuffer::upload_indexes(const std::vector<glm::uint>& points) noexcept
    {
        auto glid = upload_impl(GL_ELEMENT_ARRAY_BUFFER, points);
        indexes.emplace_back(ShapeType::POINTS, points.size(), glid);
    }

    void VertexBuffer::upload_indexes(const std::vector<glm::uvec2>& lines) noexcept
    {
        auto glid = upload_impl(GL_ELEMENT_ARRAY_BUFFER, lines);
        indexes.emplace_back(ShapeType::LINES, lines.size(), glid);
    }

    void VertexBuffer::upload_indexes(const std::vector<glm::uvec3>& faces) noexcept
    {
        auto glid = upload_impl(GL_ELEMENT_ARRAY_BUFFER, faces);
        indexes.emplace_back(ShapeType::TRIANGLES, faces.size(), glid);
    }

    void VertexBuffer::bind(Shader& shader) noexcept
    {
        glBindVertexArray(vao);
        GLOW_CHECK_ERROR();

        for (auto& info: buffers)
        {
            info.adr = shader.get_attribute(info.attribute);
            if (info.adr != -1)
            {
                glBindBuffer(GL_ARRAY_BUFFER, info.glid);
                glVertexAttribPointer(info.adr, info.stride, GL_FLOAT, GL_FALSE, 0, 0);
                glEnableVertexAttribArray(info.adr);
                GLOW_CHECK_ERROR();
            }
        }
    }

    void VertexBuffer::draw(unsigned int set) noexcept
    {
        check(set < indexes.size());

        auto& info = indexes[set];

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.glid);
        switch (info.type)
        {
            case ShapeType::POINTS:
                glDrawElements(GL_POINTS, info.count, GL_UNSIGNED_INT, 0);
                break;
            case ShapeType::LINES:
                glDrawElements(GL_LINES, info.count * 2, GL_UNSIGNED_INT, 0);
                break;
            case ShapeType::TRIANGLES:
                glDrawElements(GL_TRIANGLES, info.count * 3, GL_UNSIGNED_INT, 0);
                break;
        }
        GLOW_CHECK_ERROR();
    }
}
