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

#include <pkzo/Mesh.h>

#include <pkzo/Window.h>

#include <glm/gtc/matrix_transform.hpp>

#include "glm_gtest.h"
#include "pkzo_test.h"

TEST(Mesh, create_empty_without_OpenGL)
{
    auto mesh  = pkzo::Mesh{};

    EXPECT_EQ(0u, mesh.get_vertex_count());
    EXPECT_EQ(0u, mesh.get_triangle_count());
}

TEST(Mesh, create_plane_without_OpenGL)
{
    auto mesh  = pkzo::Mesh::create_plane({150.0f, 150.0f});

    EXPECT_EQ(4u, mesh->get_vertex_count());
    EXPECT_EQ(2u, mesh->get_triangle_count());
}