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

#include "MockGraphicSystem.h"
#include "MockRenderer.h"

using namespace ::testing;
using namespace glm;

TEST(Camera, default_contruct)
{
    auto camera = pkzo::Camera();
    EXPECT_GLM_NEAR(glm::mat4(1.0),      camera.get_transform(), 1e-4f);
    EXPECT_NEAR(90.0f,                   camera.get_fov(),       1e-4f);
    EXPECT_GLM_EQ(glm::uvec2(1600, 900), camera.get_resolution());
}

TEST(Camera, init)
{
    auto tra    = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 2.0f, -3.0f));
    auto camera = pkzo::Camera(tra, 75.0f, glm::uvec2(800, 600));
    EXPECT_GLM_NEAR(tra,                camera.get_transform(), 1e-4f);
    EXPECT_NEAR(75.0f,                  camera.get_fov(),       1e-4f);
    EXPECT_GLM_EQ(glm::uvec2(800, 600), camera.get_resolution());
}

TEST(Camera, registers_on_renderer)
{
    auto engine = pkzo::Engine{};
    auto gs = engine.start_system<StrictMock<pkzo::test::MockGraphicSystem>>();

    auto renderer = std::make_unique<StrictMock<pkzo::test::MockRenderer>>();

    auto transform  = inverse(lookAt(vec3(-10.0f, 0.5f, 2.0f), vec3(0.0f), vec3(0.0, 0.0, 0.1)));
    auto resolution = uvec2(800, 600);
    auto fov        = 101.0f;

    InSequence s;

    EXPECT_CALL(*gs, create_renderer(pkzo::RendererType::PHYSICAL))
        .WillOnce(Return(renderer.get()));

    EXPECT_CALL(*renderer, add_camera(transform, resolution, fov))
        .WillOnce(Return(42));
    EXPECT_CALL(*renderer, remove_camera(42));

    EXPECT_CALL(*gs, release_renderer(renderer.get()));

    auto scene = std::make_shared<pkzo::Scene>();

    auto camera = std::make_shared<pkzo::Camera>(transform, fov, resolution);
    scene->add_node(camera);

    engine.set_scene(scene);

    engine.run(5u);
}

TEST(Camera, updates_renderer_view)
{
    auto engine = pkzo::Engine{};
    auto gs = engine.start_system<StrictMock<pkzo::test::MockGraphicSystem>>();

    auto renderer = std::make_unique<StrictMock<pkzo::test::MockRenderer>>();

    auto transform  = inverse(lookAt(vec3(-10.0f, 0.5f, 2.0f), vec3(0.0f), vec3(0.0, 0.0, 0.1)));
    auto resolution = uvec2(800, 600);
    auto fov        = 101.0f;

    InSequence s;

    EXPECT_CALL(*gs, create_renderer(pkzo::RendererType::PHYSICAL))
        .WillOnce(Return(renderer.get()));

    EXPECT_CALL(*renderer, add_camera(transform, resolution, fov))
        .WillOnce(Return(42));
    EXPECT_CALL(*renderer, upate_camera_view(42, _));
    EXPECT_CALL(*renderer, remove_camera(42));

    EXPECT_CALL(*gs, release_renderer(renderer.get()));

    auto scene = std::make_shared<pkzo::Scene>();

    auto camera = std::make_shared<pkzo::Camera>(transform, fov, resolution);
    scene->add_node(camera);

    engine.set_scene(scene);

    engine.on_tick([&] () {
        auto t2 = glm::translate(transform, glm::vec3(0.0f, 0.0f, 1.0f));
        camera->set_transform(t2);
    });

    engine.run(1u);
}

TEST(Camera, updates_renderer_view_default_construct)
{
    auto engine = pkzo::Engine{};
    auto gs = engine.start_system<StrictMock<pkzo::test::MockGraphicSystem>>();

    auto renderer = std::make_unique<StrictMock<pkzo::test::MockRenderer>>();

    auto transform  = inverse(lookAt(vec3(-10.0f, 0.5f, 2.0f), vec3(0.0f), vec3(0.0, 0.0, 0.1)));
    auto resolution = uvec2(800, 600);
    auto fov        = 101.0f;

    InSequence s;

    EXPECT_CALL(*gs, create_renderer(pkzo::RendererType::PHYSICAL))
        .WillOnce(Return(renderer.get()));

    EXPECT_CALL(*renderer, add_camera(_, _, _))
        .WillOnce(Return(42));
    EXPECT_CALL(*renderer, upate_camera_view(42, _));
    EXPECT_CALL(*renderer, remove_camera(42));

    EXPECT_CALL(*gs, release_renderer(renderer.get()));

    auto scene = std::make_shared<pkzo::Scene>();

    auto camera = std::make_shared<pkzo::Camera>();
    scene->add_node(camera);

    engine.set_scene(scene);

    engine.on_tick([&] () {
        auto t2 = glm::translate(transform, glm::vec3(0.0f, 0.0f, 1.0f));
        camera->set_transform(t2);
    });

    engine.run(1u);
}
