// pkzo
// Copyright 2023-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include <pkzo/Material.h>

using namespace testing;

TEST(Material, save_load_no_textures)
{
    auto orig = pkzo::Material();

    orig.set_base_color_factor({1.0f, 0.0f, 0.0f, 1.0f});
    orig.set_metallic_factor(0.5f);
    orig.set_roughness_factor(0.6f);
    orig.set_emissive_factor({0.0f, 1.0f, 0.0f});
    orig.set_alpha_mode(pkzo::AlphaMode::BLEND);

    auto file = get_test_output() / "save_load_no_textures.json";
    orig.save(file);

    auto loaded = pkzo::Material(file);

    EXPECT_EQ(file, loaded.get_file());
    EXPECT_EQ(orig.get_alpha_mode(), loaded.get_alpha_mode());
    EXPECT_EQ(orig.get_base_color_factor(), loaded.get_base_color_factor());
    EXPECT_EQ(orig.get_base_color_map(), loaded.get_base_color_map());
    EXPECT_EQ(orig.get_metallic_factor(), loaded.get_metallic_factor());
    EXPECT_EQ(orig.get_roughness_factor(), loaded.get_roughness_factor());
    EXPECT_EQ(orig.get_metallic_roughness_map(), loaded.get_metallic_roughness_map());
    EXPECT_EQ(orig.get_emissive_factor(), loaded.get_emissive_factor());
    EXPECT_EQ(orig.get_emissive_map(), loaded.get_emissive_map());
    EXPECT_EQ(orig.get_normal_map(), loaded.get_normal_map());
}

TEST(Material, save_load_with_textures)
{
    auto orig = pkzo::Material();

    auto base_color         = std::make_shared<pkzo::Image>(get_test_input() / "textures/TestOrange_albedo.png");
    auto metallic_roughness = std::make_shared<pkzo::Image>(get_test_input() / "textures/TestOrange_orm.png");
    auto emissive           = std::make_shared<pkzo::Image>(get_test_input() / "textures/TestOrange_emissive.png");
    auto normal             = std::make_shared<pkzo::Image>(get_test_input() / "textures/TestOrange_normal.png");

    orig.set_base_color_factor({1.0f, 0.0f, 0.0f, 1.0f});
    orig.set_base_color_map(base_color);
    orig.set_metallic_factor(0.5f);
    orig.set_roughness_factor(0.6f);
    orig.set_metallic_roughness_map(metallic_roughness);
    orig.set_emissive_map(emissive);
    orig.set_normal_map(normal);

    auto file = get_test_output() / "save_load_with_textures.json";
    orig.save(file);

    auto loaded = pkzo::Material(file);

    EXPECT_EQ(file, loaded.get_file());
    EXPECT_EQ(orig.get_alpha_mode(), loaded.get_alpha_mode());
    EXPECT_EQ(orig.get_base_color_factor(), loaded.get_base_color_factor());
    ASSERT_NE(loaded.get_base_color_map(), nullptr);
    EXPECT_EQ(orig.get_base_color_map()->get_file(), loaded.get_base_color_map()->get_file());
    EXPECT_EQ(orig.get_metallic_factor(), loaded.get_metallic_factor());
    EXPECT_EQ(orig.get_roughness_factor(), loaded.get_roughness_factor());
    ASSERT_NE(loaded.get_metallic_roughness_map(), nullptr);
    EXPECT_EQ(orig.get_metallic_roughness_map()->get_file(), loaded.get_metallic_roughness_map()->get_file());
    EXPECT_EQ(orig.get_emissive_factor(), loaded.get_emissive_factor());
    ASSERT_NE(loaded.get_emissive_map(), nullptr);
    EXPECT_EQ(orig.get_emissive_map()->get_file(), loaded.get_emissive_map()->get_file());
    ASSERT_NE(loaded.get_normal_map(), nullptr);
    EXPECT_EQ(orig.get_normal_map()->get_file(), loaded.get_normal_map()->get_file());
}

TEST(Material, load_test_orange)
{
    auto file = get_test_input() / "materials/TestOrange.json";
    auto material = pkzo::Material(file);

    EXPECT_EQ(file, material.get_file());
    EXPECT_EQ(pkzo::AlphaMode::OPAQUE, material.get_alpha_mode());
    EXPECT_EQ(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), material.get_base_color_factor());
    ASSERT_NE(material.get_base_color_map(), nullptr);
    EXPECT_EQ(get_test_input() / "textures/TestOrange_albedo.png", material.get_base_color_map()->get_file());
    EXPECT_EQ(1.0f, material.get_metallic_factor());
    EXPECT_EQ(1.0f, material.get_roughness_factor());
    ASSERT_NE(material.get_metallic_roughness_map(), nullptr);
    EXPECT_EQ(get_test_input() / "textures/TestOrange_orm.png", material.get_metallic_roughness_map()->get_file());
    EXPECT_EQ(glm::vec3(0.0f, 0.0f, 0.0f), material.get_emissive_factor());
    ASSERT_EQ(material.get_emissive_map(), nullptr);
    ASSERT_NE(material.get_normal_map(), nullptr);
    EXPECT_EQ(get_test_input() / "textures/TestOrange_normal.png", material.get_normal_map()->get_file());
}


