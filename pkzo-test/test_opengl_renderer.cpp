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

TEST(OpenGLRenderer, GRAPHICAL_shapes)
{
    auto engine = pkzo::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto scene = std::make_shared<pkzo::Scene>();

    // camera
    auto ct = pkzo::lookat({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    auto camera = std::make_shared<pkzo::Camera>(ct, 90.0f, glm::uvec2(800, 600));
    scene->add_node(camera);

    // lights
    auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene->add_node(light0);

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    auto light1 = std::make_shared<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
    scene->add_node(light1);

    auto light2 = std::make_shared<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
    scene->add_node(light2);

    // action
    auto material = pkzo::make_simple_material(glm::vec3(0.75f));

    auto box = std::make_shared<pkzo::BoxVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, 0.0f}), glm::vec3(1.0f), material);
    scene->add_node(box);

    auto sphere = std::make_shared<pkzo::SphereVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), 0.5f, material);
    scene->add_node(sphere);

    engine.set_scene(scene);

    engine.run(3);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(OpenGLRenderer, GRAPHICAL_emissive)
{
    auto engine = pkzo::Engine{};

    engine.add_asset_folder(pkzo::test::get_test_input());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto scene = std::make_shared<pkzo::Scene>();

    // camera
    auto ct = pkzo::lookat({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    auto camera = std::make_shared<pkzo::Camera>(ct, 90.0f, glm::uvec2(800, 600));
    scene->add_node(camera);

    // lights
    auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene->add_node(light0);

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    auto light1 = std::make_shared<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
    scene->add_node(light1);

    auto light2 = std::make_shared<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
    scene->add_node(light2);

    // action
    auto opaque   = pkzo::make_simple_material(glm::vec3(0.75f));
    auto emissive = pkzo::make_emissive_material(glm::vec3(1.0, 0.5, 0.5), engine.load_asset<pkzo::Texture>("rectangle.png"));
    emissive->set_base_color_factor(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));

    auto box = std::make_shared<pkzo::BoxVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, 0.0f}), glm::vec3(1.0f), emissive);
    scene->add_node(box);

    auto sphere = std::make_shared<pkzo::SphereVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), 0.5f, opaque);
    scene->add_node(sphere);

    engine.set_scene(scene);

    engine.run(3);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(OpenGLRenderer, GRAPHICAL_point_light)
{
    auto engine = pkzo::Engine{};

    engine.add_asset_folder(pkzo::test::get_test_input());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto scene = std::make_shared<pkzo::Scene>();

    // camera
    auto ct = pkzo::lookat({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    auto camera = std::make_shared<pkzo::Camera>(ct, 90.0f, glm::uvec2(800, 600));
    scene->add_node(camera);

    // lights
    auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene->add_node(light0);

    auto light1 = std::make_shared<pkzo::PointLight>(glm::translate(glm::mat4{1.0f}, {-0.5f, -0.6f, 1.0f}), glm::vec3(0.839, 0.718, 0.573));
    scene->add_node(light1);

    // action
    auto opaque   = pkzo::make_simple_material(glm::vec3(0.75f));

    auto ground = std::make_shared<pkzo::BoxVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, -0.5f}), glm::vec3(10.0f, 10.0f, 1.0f), opaque);
    scene->add_node(ground);

    auto sphere = std::make_shared<pkzo::SphereVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, 0.5f}), 0.25f, opaque);
    scene->add_node(sphere);

    engine.set_scene(scene);

    engine.run(3);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(OpenGLRenderer, GRAPHICAL_spot_light)
{
    auto engine = pkzo::Engine{};

    engine.add_asset_folder(pkzo::test::get_test_input());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto scene = std::make_shared<pkzo::Scene>();

    // camera
    auto ct = pkzo::lookat({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    auto camera = std::make_shared<pkzo::Camera>(ct, 90.0f, glm::uvec2(800, 600));
    scene->add_node(camera);

    // lights
    auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene->add_node(light0);

    auto l1t = pkzo::lookat(glm::vec3{-1.0f, -0.6f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0, 1.0, 0.0});
    auto light1 = std::make_shared<pkzo::SpotLight>(l1t, glm::vec3(0.839, 0.718, 0.573), 25.0f, 30.0f);
    scene->add_node(light1);

    // action
    auto opaque   = pkzo::make_simple_material(glm::vec3(0.75f));

    auto ground = std::make_shared<pkzo::BoxVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, -0.5f}), glm::vec3(10.0f, 10.0f, 1.0f), opaque);
    scene->add_node(ground);

    auto sphere = std::make_shared<pkzo::SphereVisual>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, 0.5f}), 0.25f, opaque);
    scene->add_node(sphere);

    engine.set_scene(scene);

    engine.run(3);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

