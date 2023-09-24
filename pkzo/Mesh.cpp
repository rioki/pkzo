// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "Mesh.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"
#include "opengl.h"
#include "Shader.h"

namespace pkzo
{
    using opengl::check_glerror;

    std::shared_ptr<Mesh> Mesh::create_plane(const glm::vec2& size)
    {
        const auto hs = size * 0.5f;

        auto mesh = std::make_shared<Mesh>();

        mesh->add_vertex({-hs.x, -hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});

        mesh->add_triangle(0, 1, 2);
        mesh->add_triangle(0, 2, 3);

        return mesh;
    }

    Mesh::~Mesh()
    {
        release();
    }

    void Mesh::add_vertex(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& texcoord)
    {
        vertices.emplace_back(vertex, normal, tangent, texcoord);
    }

    void Mesh::add_triangle(uint a, uint b, uint c)
    {
        triangles.push_back({a, b, c});
    }

    uint Mesh::get_vertex_count() const noexcept
    {
        return static_cast<uint>(vertices.size());
    }

    uint Mesh::get_triangle_count() const noexcept
    {
        return static_cast<uint>(triangles.size());
    }

    void Mesh::upload()
    {
        if (is_uploaded())
        {
            return;
        }

        vertex_buffer = std::make_shared<opengl::VertexBuffer>();
        vertex_buffer->upload_values({3, 3, 3, 2}, static_cast<uint>(vertices.size()), glm::value_ptr(vertices[0].vertex));
        vertex_buffer->upload_indexes(triangles);
    }

    bool Mesh::is_uploaded() const noexcept
    {
        return vertex_buffer != nullptr;
    }

    void Mesh::release()
    {
        vertex_buffer = nullptr;
    }

    void Mesh::draw()
    {
        if (!is_uploaded())
        {
            upload();
        }

        check(vertex_buffer != nullptr);
        vertex_buffer->draw();
    }
}

