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

#include <gtest/gtest.h>
#include <pkzo/pkzo.h>

#include "glm_gtest.h"
#include "pkzo_gtest.h"

TEST(render3d, empty)
{
    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}

TEST(render3d, ambient_light)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::AmbientLight>({
        .color = glm::vec3(0.55, 0.58, 0.65) * 0.1f
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}

TEST(render3d, directional_light)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::DirectionalLight>({
        .transform = pkzo::lookat(glm::vec3(1.4f, 1.5f, 2.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        .color     = glm::vec3(0.55, 0.58, 0.65)
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}

TEST(render3d, point_light)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::PointLight>({
        .transform  = pkzo::lookat(glm::vec3(1.4f, 1.5f, 2.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        .color      = glm::vec3(0.55, 0.58, 0.65)
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}

TEST(render3d, spot_light)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::SpotLight>({
        .transform  = pkzo::lookat(glm::vec3(1.4f, 1.5f, 2.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        .color      = glm::vec3(0.55, 0.58, 0.65)
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}

TEST(render3d, skybox_chinease_garden)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");
    auto plain_gray  = pkzo::Material::load(base / "materials/PlainGray.yml");
    auto hdri        = pkzo::Texture::load_file({
        .file  = base / "polyhaven/hdri/chinese_garden_1k.exr",
        .clamp = pkzo::Clamp::CLAMP_HORIZONTAL
    });

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::SkyBox>({
        .texture  = hdri
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::SphereGeometry>({
        .transform     = pkzo::position(0.0f, 2.0f, 0.5f),
        .diameter      = 1.0f,
        .material      = plain_gray
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}


TEST(render3d, skybox_qwantani_dusk)
{
    auto base = pkzo::test::get_test_input();
    auto test_gray   = pkzo::Material::load(base / "materials/TestGray.yml");
    auto test_orange = pkzo::Material::load(base / "materials/TestOrange.yml");
    auto hdri        = pkzo::Texture::load_file({
        .file  = base / "polyhaven/hdri/qwantani_dusk_2_puresky_1k.exr",
        .clamp = pkzo::Clamp::CLAMP_HORIZONTAL
    });

    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    auto scene = pkzo::Scene();

    scene.add<pkzo::SkyBox>({
        .texture  = hdri
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
        .size          = glm::vec3(10.0f, 10.0f, 1.0f),
        .texture_scale = glm::vec3(10.0f, 10.0f, 1.0f),
        .material      = test_gray
    });

    scene.add<pkzo::BoxGeometry>({
        .transform     = pkzo::position(0.0f, 0.0f, 0.5f),
        .size          = glm::vec3(1.0f),
        .texture_scale = glm::vec3(1.0f),
        .material      = test_orange
    });

    scene.add<pkzo::Camera>({
        .transform = pkzo::lookat(glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f))
    });

    window.on_draw([&] (auto& gc) {
        scene.draw(gc);
    });

    window.draw();
    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}
