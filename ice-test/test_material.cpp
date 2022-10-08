// Ice Engine
// Copyright 2022 Sean Farrell
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

#include <ice/ice.h>

TEST(Material, default_contruct)
{
    auto material = ice::Material();
    EXPECT_GLM_NEAR(glm::vec4(1.0f), material.get_base_color_factor(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec3(0.0f), material.get_emissive_factor(), 1e-4f);
    EXPECT_EQ(nullptr, material.get_base_color_map());
    EXPECT_EQ(nullptr, material.get_emissive_map());
}

TEST(Material, make_simple)
{
    auto material = ice::make_simple_material(glm::vec3(0.1, 0.2, 0.3));
    EXPECT_GLM_NEAR(glm::vec4(0.1, 0.2, 0.3, 1.0f), material->get_base_color_factor(), 1e-4f);
    EXPECT_EQ(nullptr, material->get_base_color_map());
}

TEST(Material, make_simple_map)
{
    auto texture = std::make_shared<ice::Texture>(glm::vec2(1,1), ice::ColorMode::RGB, ice::DataType::UINT8, "test");
    auto material = ice::make_simple_material(texture);
    EXPECT_GLM_NEAR(glm::vec4(1.f), material->get_base_color_factor(), 1e-4f);
    EXPECT_EQ(texture, material->get_base_color_map());
}

TEST(Material, emissive)
{
    auto texture = std::make_shared<ice::Texture>(glm::vec2(1,1), ice::ColorMode::RGB, ice::DataType::UINT8, "test");

    auto material = std::make_shared<ice::Material>();
    material->set_emissive_factor(glm::vec3(0.8f, 0.7f, 0.6f));
    material->set_emissive_map(texture);

    EXPECT_GLM_EQ(glm::vec3(0.8f, 0.7f, 0.6f), material->get_emissive_factor());
    EXPECT_EQ(texture, material->get_emissive_map());
}

TEST(Material, make_emissive_factor)
{
    auto material = ice::make_emissive_material(glm::vec3(0.8f, 0.7f, 0.6f));

    EXPECT_GLM_EQ(glm::vec4(0.0f),             material->get_base_color_factor());
    EXPECT_GLM_EQ(glm::vec3(0.8f, 0.7f, 0.6f), material->get_emissive_factor());
    EXPECT_EQ(    nullptr,                     material->get_emissive_map());
}

TEST(Material, make_emissive_map)
{
    auto texture = std::make_shared<ice::Texture>(glm::vec2(1,1), ice::ColorMode::RGB, ice::DataType::UINT8, "test");

    auto material = ice::make_emissive_material(texture);

    EXPECT_GLM_EQ(glm::vec4(0.0f), material->get_base_color_factor());
    EXPECT_GLM_EQ(glm::vec3(1.0f), material->get_emissive_factor());
    EXPECT_EQ(    texture,         material->get_emissive_map());
}

TEST(Material, make_emissive_factor_map)
{
    auto texture = std::make_shared<ice::Texture>(glm::vec2(1,1), ice::ColorMode::RGB, ice::DataType::UINT8, "test");

    auto material = ice::make_emissive_material(glm::vec3(0.8f, 0.7f, 0.6f), texture);

    EXPECT_GLM_EQ(glm::vec4(0.0f),             material->get_base_color_factor());
    EXPECT_GLM_EQ(glm::vec3(0.8f, 0.7f, 0.6f), material->get_emissive_factor());
    EXPECT_EQ(    texture,                     material->get_emissive_map());
}