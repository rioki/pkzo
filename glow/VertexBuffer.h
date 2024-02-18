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

#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "defines.h"
#include "Shader.h"

namespace glow
{
    enum class ShapeType
    {
        POINTS,
        LINES,
        TRIANGLES
    };

    class GLOW_EXPORT VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void upload_values(const std::string& attrib, const std::vector<glm::vec2>& values) noexcept;
        void upload_values(const std::string& attrib, const std::vector<glm::vec3>& values) noexcept;
        void upload_values(const std::string& attrib, const std::vector<glm::vec4>& values) noexcept;

        void upload_indexes(const std::vector<glm::uint>& points) noexcept;
        void upload_indexes(const std::vector<glm::uvec2>& lines) noexcept;
        void upload_indexes(const std::vector<glm::uvec3>& faces) noexcept;

        void bind(Shader& shader) noexcept;
        void draw(unsigned int set = 0) noexcept;

    private:
        struct BufferInfo
        {
            std::string  attribute;
            unsigned int stride;
            unsigned int count;
            unsigned int glid;
            unsigned int adr;
        };

        struct IndexInfo
        {
            ShapeType type;
            unsigned int count;
            unsigned int glid;
        };

        unsigned int vao = 0;
        std::vector<BufferInfo> buffers;
        std::vector<IndexInfo>  indexes;

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator = (const VertexBuffer&) = delete;
    };
}
