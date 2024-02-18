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

#include "pch.h"
#include "Mesh.h"

namespace pkzo
{
    unsigned int Mesh::add_vertex(const glm::vec3& position, const glm::vec2& tex_coord) noexcept
    {
        return add_vertex(position, glm::vec3(0.0f), glm::vec3(0.0f), tex_coord);
    }

    unsigned int Mesh::add_vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& tex_coord) noexcept
    {
        return add_vertex(position, normal, glm::vec3(0.0f), tex_coord);
    }

    unsigned int Mesh::add_vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& tex_coord) noexcept
    {
        positions.push_back(position);
        normals.push_back(normal);
        tangents.push_back(tangent);
        texcoords.push_back(tex_coord);

        return static_cast<unsigned int>(positions.size() - 1);
    }

    void Mesh::add_triangle(unsigned int a, unsigned int b, unsigned int c) noexcept
    {
        triangles.emplace_back(a, b, c);
    }

    const std::vector<glm::vec3>& Mesh::get_positions() const noexcept
    {
        return positions;
    }

    const std::vector<glm::vec3>& Mesh::get_normals() const noexcept
    {
        return normals;
    }

    const std::vector<glm::vec3>& Mesh::get_tangents() const noexcept
    {
        return tangents;
    }

    const std::vector<glm::vec2>& Mesh::get_texcoords() const noexcept
    {
        return texcoords;
    }

    const std::vector<glm::uvec3>& Mesh::get_triangles() const noexcept
    {
        return triangles;
    }

    void Mesh::calculate_normals() noexcept
    {
        check(positions.size() == normals.size());

        for (const auto& triangle : triangles)
        {
            auto a = positions[triangle.x];
            auto b = positions[triangle.y];
            auto c = positions[triangle.z];

            auto n = glm::normalize(glm::cross(b - a, c - a));

            normals[triangle.x] += n;
            normals[triangle.y] += n;
            normals[triangle.z] += n;
        }

        for (auto& normal : normals)
        {
            normal = glm::normalize(normal);
        }
    }

    void Mesh::calculate_tangents() noexcept
    {
        check(positions.size() == tangents.size());

        for (const auto& triangle : triangles)
        {
            auto a = positions[triangle.x];
            auto b = positions[triangle.y];
            auto c = positions[triangle.z];

            auto ab = b - a;
            auto ac = c - a;

            auto uv_a = texcoords[triangle.x];
            auto uv_b = texcoords[triangle.y];
            auto uv_c = texcoords[triangle.z];

            auto duv_ab = uv_b - uv_a;
            auto duv_ac = uv_c - uv_a;

            auto f = 1.0f / (duv_ab.x * duv_ac.y - duv_ac.x * duv_ab.y);

            auto t = glm::normalize(glm::vec3(
                f * (duv_ac.y * ab.x - duv_ab.y * ac.x),
                f * (duv_ac.y * ab.y - duv_ab.y * ac.y),
                f * (duv_ac.y * ab.z - duv_ab.y * ac.z)
            ));

            tangents[triangle.x] += t;
            tangents[triangle.y] += t;
            tangents[triangle.z] += t;
        }

        for (auto& tangent : tangents)
        {
            tangent = glm::normalize(tangent);
        }
    }

    Mesh create_rectangle(glm::vec2 size) noexcept
    {
        auto hs = size * 0.5f;

        auto mesh = Mesh{};

        auto a = mesh.add_vertex(glm::vec3(-hs.x, -hs.y, 0.0f), glm::vec2(0.0f, 0.0f));
        auto b = mesh.add_vertex(glm::vec3( hs.x, -hs.y, 0.0f), glm::vec2(1.0f, 0.0f));
        auto c = mesh.add_vertex(glm::vec3( hs.x,  hs.y, 0.0f), glm::vec2(1.0f, 1.0f));
        auto d = mesh.add_vertex(glm::vec3(-hs.x,  hs.y, 0.0f), glm::vec2(0.0f, 1.0f));

        mesh.add_triangle(a, b, c);
        mesh.add_triangle(a, c, d);

        mesh.calculate_normals();
        mesh.calculate_tangents();

        return mesh;
    }

    Mesh create_screen_rectangle() noexcept
    {
        return create_rectangle(glm::vec2(2.0f));
    }
}
