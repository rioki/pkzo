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

#include <pkzo-three/Material.h>
#include <pkzo-three/SceneGroup.h>
#include <glm/gtc/matrix_transform.hpp>

#include <gtest/gtest.h>
#include "glm_gtest.h"

TEST(Material, rbg_hex)
{
    glm::vec3 expected(1.0f, 0.0f, 0.0f);
    glm::vec3 result = pkzo::three::rgb(0xFF0000);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}

TEST(Material, rbga_hex)
{
    glm::vec4 expected(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 result = pkzo::three::rgba(0xFF0000FF);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}

TEST(Material, rbg_components)
{
    glm::vec3 expected(0.0f, 1.0f, 0.0f);
    glm::vec3 result = pkzo::three::rgb(0u, 255u, 0u);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}

TEST(Material, rbga_components)
{
    glm::vec4 expected(0.0f, 0.0f, 1.0f, 0.49803);
    glm::vec4 result = pkzo::three::rgba(0u, 0u, 255u, 127u);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}

TEST(Material, rgb_passthrough)
{
    glm::vec3 expected(0.2f, 0.4f, 0.6f);
    glm::vec3 result = pkzo::three::rgb(0.2f, 0.4f, 0.6f);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}

TEST(Material, rgba_passthrough)
{
    glm::vec4 expected(0.1f, 0.2f, 0.3f, 0.5f);
    glm::vec4 result = pkzo::three::rgba(0.1f, 0.2f, 0.3f, 0.5f);
    EXPECT_GLM_NEAR(result, expected, 1e-4f);
}
