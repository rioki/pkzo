// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include <vector>

#include <glm/glm.hpp>

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Mesh
    {
    public:
        Mesh() noexcept = default;
        ~Mesh() noexcept = default;

        Mesh(const Mesh&) = default;
        Mesh& operator = (const Mesh&) = default;

        Mesh(Mesh&&) = default;
        Mesh& operator = (Mesh&&) = default;

        unsigned int add_vertex(const glm::vec3& position, const glm::vec2& tex_coord) noexcept;
        unsigned int add_vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& tex_coord) noexcept;
        unsigned int add_vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& tex_coord) noexcept;

        void add_triangle(unsigned int a, unsigned int b, unsigned int c) noexcept;

        const std::vector<glm::vec3>& get_positions() const noexcept;
        const std::vector<glm::vec3>& get_normals() const noexcept;
        const std::vector<glm::vec3>& get_tangents() const noexcept;
        const std::vector<glm::vec2>& get_texcoords() const noexcept;

        const std::vector<glm::uvec3>& get_triangles() const noexcept;

        void calculate_normals() noexcept;
        void calculate_tangents() noexcept;

    private:
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec2> texcoords;

        std::vector<glm::uvec3> triangles;
    };

    Mesh create_rectangle(glm::vec2 size) noexcept;
    Mesh create_screen_rectangle() noexcept;
}
