// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "Mesh.h"

namespace pkzo
{
    glm::uint Mesh::add_vertex(const glm::vec3 position, const glm::vec2& texcoord) noexcept
    {
        return add_vertex(position, {0.0, 0.0, 0.0}, texcoord);
    }

    glm::uint Mesh::add_vertex(const glm::vec3 position, const glm::vec3& normal, const glm::vec2& texcoord) noexcept
    {
        increment_version();
        vertices.push_back(position);
        normals.push_back(normal);
        texcoords.push_back(texcoord);
        return static_cast<glm::uint>(vertices.size() - 1);
    }

    void Mesh::add_triangle(const glm::uvec3& face) noexcept
    {
        increment_version();
        faces.push_back(face);
    }

    const std::vector<glm::vec3>& Mesh::get_vertices() const noexcept
    {
        return vertices;
    }

    const std::vector<glm::vec3>& Mesh::get_normals() const noexcept
    {
        return normals;
    }

    const std::vector<glm::vec2>& Mesh::get_texcoords() const noexcept
    {
        return texcoords;
    }

    const std::vector<glm::uvec3>& Mesh::get_faces() const noexcept
    {
        return faces;
    }

    std::shared_ptr<Mesh> make_rectangle_mesh(const glm::vec2& size) noexcept
    {
        auto hs = size * 0.5f;
        auto mesh = std::make_unique<Mesh>();

        mesh->add_vertex({-hs.x, -hs.y, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, 0.0f}, {1.0f, 0.0f});

        mesh->add_triangle({0, 1, 2});
        mesh->add_triangle({2, 3, 0});

        return mesh;
    }

    std::shared_ptr<Mesh> make_box_mesh(const glm::vec3& size) noexcept
    {
        auto mesh = std::make_shared<Mesh>();

        auto hs = size / 2.0f;

        // x pos
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f});
        // x neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f});
        // y pos
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  0.0f});
        // y neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 0.0f, -1.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, { 0.0f, -1.0f,  0.0f}, { 0.0f,  0.0f});
        // z pos
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f});
        // z neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f});

        // x pos
        mesh->add_triangle({ 0,  1,  2});
        mesh->add_triangle({ 0,  2,  3});
        // x neg
        mesh->add_triangle({ 6,  5,  4});
        mesh->add_triangle({ 7,  4,  6});
        // y pos
        mesh->add_triangle({ 8,  9, 10});
        mesh->add_triangle({ 8, 10, 11});
        // y neg
        mesh->add_triangle({14, 13, 12});
        mesh->add_triangle({15, 12, 14});
        // z pos
        mesh->add_triangle({16, 17, 18});
        mesh->add_triangle({16, 18, 19});
        // z neg
        mesh->add_triangle({22, 21, 20});
        mesh->add_triangle({23, 20, 22});

        return mesh;
    }

    std::shared_ptr<Mesh> make_sphere_mesh(float radius, unsigned int sectors, unsigned int rings) noexcept
    {
        constexpr auto PI = static_cast<float>(std::numbers::pi);

        auto mesh = std::make_shared<Mesh>();

        auto R = 1.0/static_cast<float>(rings-1);
        auto S = 1.0/static_cast<float>(sectors-1);

        for(auto r = 0u; r < rings; r++)
        {
            for(auto s = 0u; s < sectors; s++)
            {
                auto x = std::cos(2*PI * s * S) * std::sin(PI * r * R);
                auto y = std::sin(2*PI * s * S) * std::sin(PI * r * R);
                auto z = std::sin(-PI/2.0 + PI * r * R);
                mesh->add_vertex({x * radius, y * radius, z * radius}, {x, y, z}, {s*S, r*R});
            }
        }

        for (auto r = 0u; r < (rings-1); r++)
        {
            for(auto s = 0u; s < (sectors-1); s++)
            {
                auto a = r * sectors + s;
                auto b = r * sectors + (s+1);
                auto c = (r+1) * sectors + (s+1);
                auto d = (r+1) * sectors + s;
                mesh->add_triangle({a, b, c});
                mesh->add_triangle({c, d, a});
            }
        }
        return mesh;
    }
}
