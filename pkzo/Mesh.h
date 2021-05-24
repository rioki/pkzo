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

#pragma once

#include "config.h"

#include <memory>
#include <array>
#include <glm/glm.hpp>

namespace pkzo
{
    class Shader;

    class PKZO_EXPORT Mesh
    {
    public:
        Mesh() noexcept;
        Mesh(const Mesh&) = delete;
        ~Mesh();
        Mesh& operator = (const Mesh&) = delete;

        glm::uint add_vertex(const glm::vec3 position, const glm::vec2& texcoord) noexcept;
        glm::uint add_vertex(const glm::vec3 position, const glm::vec3& normal, const glm::vec2& texcoord) noexcept;

        void add_triangle(const glm::uvec3& face) noexcept;

        const std::vector<glm::vec3>& get_vertices() const noexcept;
        const std::vector<glm::vec3>& get_normals() const noexcept;
        const std::vector<glm::vec2>& get_texcoords() const noexcept;
        const std::vector<glm::uvec3>& get_faces() const noexcept;

        void upload() noexcept;

        void bind(Shader& shader) noexcept;

        void draw() noexcept;

    private:
        glm::uint gl_id = 0u;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::uvec3> faces;

        glm::uint                vao          = 0u;
        std::array<glm::uint, 4> buffers      = {0u, 0u};
    };

    //! Make a rectangle mesh in the X/Y plane.
    //!
    //! @param size the size of the mesh
    //! @return the mesh
    PKZO_EXPORT std::unique_ptr<Mesh> make_rectangle(const glm::vec2& size) noexcept;
}
