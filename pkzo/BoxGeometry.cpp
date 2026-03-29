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

#include "BoxGeometry.h"

namespace pkzo
{
    std::shared_ptr<Mesh> generate_box_mesh(const glm::vec3& size, const glm::vec3& texture_scale)
    {
        auto& s  = size;
        auto  hs = 0.5f * size;
        auto& ts = texture_scale;

        return Mesh::create({
            .vertexes = {
                // Front (+Z)
                {-hs.x, -hs.y,  hs.z},
                { hs.x, -hs.y,  hs.z},
                { hs.x,  hs.y,  hs.z},
                {-hs.x,  hs.y,  hs.z},
                // Back (-Z)
                {-hs.x, -hs.y, -hs.z},
                { hs.x, -hs.y, -hs.z},
                { hs.x,  hs.y, -hs.z},
                {-hs.x,  hs.y, -hs.z},
                // Left (-X)
                {-hs.x, -hs.y, -hs.z},
                {-hs.x, -hs.y,  hs.z},
                {-hs.x,  hs.y,  hs.z},
                {-hs.x,  hs.y, -hs.z},
                // Right (+X)
                { hs.x, -hs.y, -hs.z},
                { hs.x, -hs.y,  hs.z},
                { hs.x,  hs.y,  hs.z},
                { hs.x,  hs.y, -hs.z},
                // Top (+Y)
                {-hs.x,  hs.y,  hs.z},
                { hs.x,  hs.y,  hs.z},
                { hs.x,  hs.y, -hs.z},
                {-hs.x,  hs.y, -hs.z},
                // Bottom (-Y)
                {-hs.x, -hs.y,  hs.z},
                { hs.x, -hs.y,  hs.z},
                { hs.x, -hs.y, -hs.z},
                {-hs.x, -hs.y, -hs.z}
            },
            .normals = {
                // Front (+Z)
                {0, 0, 1},
                {0, 0, 1},
                {0, 0, 1},
                {0, 0, 1},
                // Back (-Z)
                {0, 0, -1},
                {0, 0, -1},
                {0, 0, -1},
                {0, 0, -1},
                // Left (-X)
                {-1, 0, 0},
                {-1, 0, 0},
                {-1, 0, 0},
                {-1, 0, 0},
                // Right (+X)
                {1, 0, 0},
                {1, 0, 0},
                {1, 0, 0},
                {1, 0, 0},
                // Top (+Y)
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                // Bottom (-Y)
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0}
            },
            .tangents = {
                // Front (+Z)
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0},
                // Back (-Z)
                {0,  1, 0},
                {0,  1, 0},
                {0,  1, 0},
                {0,  1, 0},
                // Left (-X)
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0},
                {0, -1, 0},
                // Right (+X)
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                // Top (+Y)
                {-1, 0, 0},
                {-1, 0, 0},
                {-1, 0, 0},
                {-1, 0, 0},
                // Bottom (-Y)
                { 1, 0, 0},
                { 1, 0, 0},
                { 1, 0, 0},
                { 1, 0, 0},
            },
            .texcoords = {
                // Front (+Z)
                {ts.x, 0.0f},
                {ts.x, ts.y},
                {0.0f, ts.y},
                {0.0f, 0.0f},
                // Back (-Z)
                {ts.x, 0.0f},
                {ts.x, ts.y},
                {0.0f, ts.y},
                {0.0f, 0.0f},
                // Left (-X)
                { ts.y, 0.0f},
                { ts.y, ts.z},
                {0.0f,  ts.z},
                {0.0f,       0.0f},
                // Right (+X)
                {0.0f, 0.0f},
                {0.0f, ts.z},
                {ts.y, ts.z},
                {ts.y, 0.0f},
                // Top (+Y)
                {ts.x, ts.z},
                {0.0f, ts.z},
                {0.0f, 0.0f},
                {ts.x, 0.0f},
                // Bottom (-Y)
                {0.0f, ts.z},
                {ts.x, ts.z},
                {ts.x, 0.0f},
                {0.0f, 0.0f}
            },
            .faces = {
                // +Z
                { 0,  1,  2}, { 0,  2,  3},
                // -Z  (flip)
                { 4,  6,  5}, { 4,  7,  6},
                // -X
                { 8,  9, 10}, { 8, 10, 11},
                // +X
                {12, 13, 14}, {12, 14, 15},
                // +Y
                {16, 17, 18}, {16, 18, 19},
                // -Y  (flip)
                {20, 22, 21}, {20, 23, 22}
            }
        });
    }

    BoxGeometry::BoxGeometry(Init init)
    : Geometry({
        .parent     = init.parent,
        .transform  = init.transform,
        .visible    = init.visible,
        .collidable = init.collidable,
        .material   = init.material}),
      size(init.size), texture_scale(init.texture_scale) {}

    BoxGeometry::~BoxGeometry() = default;

    void BoxGeometry::set_size(const glm::vec3& value)
    {
        size = value;
        mesh = nullptr;
    }

    glm::vec3 BoxGeometry::get_size() const
    {
        return size;
    }

    void BoxGeometry::set_texture_scale(const glm::vec3& value)
    {
        texture_scale = value;
        mesh = nullptr;
    }

    glm::vec3 BoxGeometry::get_texture_scale() const
    {
        return texture_scale;
    }

    Bounds3 BoxGeometry::get_bounds() const
    {
        auto hs = size * 0.5f;
        return Bounds3(-hs, hs);
    }

    std::shared_ptr<Mesh> BoxGeometry::get_mesh() const
    {
        if (mesh)
        {
            return mesh;
        }

        mesh = generate_box_mesh(size, texture_scale);
        return mesh;
    }
}
