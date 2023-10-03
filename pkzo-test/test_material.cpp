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
#include "pkzo_test.h"

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

TEST(Material, constructor_defaults)
{
    pkzo::three::Material material;
    EXPECT_GLM_EQ(material.get_base_color_factor(), glm::vec3(1.0f, 1.0f, 1.0f));
    EXPECT_GLM_EQ(material.get_emissive_factor(),   glm::vec3(0.0f, 0.0f, 0.0f));

    EXPECT_TEXTURE_EQ(material.get_base_color_map(),         pkzo::three::get_white_texture());
    EXPECT_TEXTURE_EQ(material.get_metallic_roughness_map(), pkzo::three::get_black_texture());
    EXPECT_TEXTURE_EQ(material.get_normal_map(),             pkzo::three::get_normal_texture());
    EXPECT_TEXTURE_EQ(material.get_occlusion_map(),          pkzo::three::get_black_texture());
    EXPECT_TEXTURE_EQ(material.get_emissive_map(),           pkzo::three::get_black_texture());
}

TEST(Material, base_color_factor)
{
    pkzo::three::Material material;
    glm::vec3 color(0.5f, 0.5f, 0.5f);
    material.set_base_color_factor(color);
    EXPECT_GLM_EQ(material.get_base_color_factor(), color);
}

TEST(Material, emissive_factor)
{
    pkzo::three::Material material;
    glm::vec3 factor(1.0f, 0.0f, 0.0f);
    material.set_emissive_factor(factor);
    EXPECT_GLM_EQ(material.get_emissive_factor(), factor);
}

TEST(Material, base_color_texture)
{
    pkzo::three::Material material;
    auto texture = pkzo::three::get_orange_texture();
    material.set_base_color_map(texture);
    EXPECT_EQ(material.get_base_color_map(), texture);
}

TEST(Material, metallic_roughness_texture)
{
    pkzo::three::Material material;
    auto texture = pkzo::three::get_orange_texture();
    material.set_metallic_roughness_map(texture);
    EXPECT_EQ(material.get_metallic_roughness_map(), texture);
}

TEST(Material, normal_texture)
{
    pkzo::three::Material material;
    auto texture = pkzo::three::get_orange_texture();
    material.set_normal_map(texture);
    EXPECT_EQ(material.get_normal_map(), texture);
}

TEST(Material, occlusion_texture)
{
    pkzo::three::Material material;
    auto texture = pkzo::three::get_orange_texture();
    material.set_occlusion_map(texture);
    EXPECT_EQ(material.get_occlusion_map(), texture);
}

TEST(Material, emissive_texture)
{
    pkzo::three::Material material;
    auto texture = pkzo::three::get_orange_texture();
    material.set_emissive_map(texture);
    EXPECT_EQ(material.get_emissive_map(), texture);
}
