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

TEST(Mesh, default_contruct)
{
    auto mesh = pkzo::Mesh();
}

TEST(Mesh, create_rectangle)
{
    auto mesh = pkzo::Mesh();

    mesh.add_vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f});
    mesh.add_vertex({-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f});
    mesh.add_vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f});
    mesh.add_vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f});

    mesh.add_triangle({0, 1, 2});
    mesh.add_triangle({2, 3, 0});

    const auto& verts = mesh.get_vertices();
    const auto& norms = mesh.get_normals();
    const auto& texco = mesh.get_texcoords();
    const auto& faces = mesh.get_faces();

    EXPECT_EQ(4u, verts.size());
    EXPECT_EQ(4u, norms.size());
    EXPECT_EQ(4u, texco.size());
    EXPECT_EQ(2u, faces.size());
}