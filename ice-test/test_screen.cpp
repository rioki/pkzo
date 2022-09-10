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

TEST(Screen, init)
{
    auto screen = ice::Screen(glm::vec2(640.0f, 480.0f));
    EXPECT_GLM_NEAR(glm::mat3(1.0), screen.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(640.0f, 480.0f), screen.get_size(), 1e-4f);
}

TEST(Screen, GRAPHICAL_render_plain_rectangle)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);

    engine.start_system<ice::GraphicSystem>();

    auto screen = std::make_shared<ice::Screen>(glm::vec2(800.0f, 600.0f));

    auto rt = glm::mat3(1.0f);
    rt = glm::translate(rt, {-25.0f, 50.0f});
    rt = glm::rotate(rt, glm::radians(35.0f));
    auto rectangle = ice::Rectangle(rt, {250.0f, 200.0f}, {1.0f, 0.7f, 0.5f, 1.0f});
    screen->add_node(rectangle);

    engine.set_overlay(screen);

    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(Screen, GRAPHICAL_render_textured_rectangle)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);

    engine.start_system<ice::GraphicSystem>();

    auto screen = std::make_shared<ice::Screen>(glm::vec2(800.0f, 600.0f));

    auto rt = glm::mat3(1.0f);
    rt = glm::translate(rt, {25.0f, -50.0f});
    rt = glm::rotate(rt, glm::radians(-35.0f));
    auto rectangle = ice::Rectangle(rt, {200.0f, 250.0f}, {1.0f, 0.7f, 0.5f, 1.0f}, std::make_shared<ice::Texture>(ice::test::get_test_input() / "AngryCat.jpg"));
    screen->add_node(rectangle);

    engine.set_overlay(screen);

    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(Screen, GRAPHICAL_render_text)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);

    engine.start_system<ice::GraphicSystem>();

    auto screen = std::make_shared<ice::Screen>(glm::vec2(800.0f, 600.0f));

    auto font = std::make_shared<ice::Font>(ice::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 32);
    auto text = std::make_shared<ice::Text>(glm::mat3(1.0f), "Ice Engine", font, glm::vec4(1.0f));
    screen->add_node(text);

    engine.set_overlay(screen);

    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}