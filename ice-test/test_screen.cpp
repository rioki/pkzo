// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/glm_2d.h>
#include <ice/glm_json.h>
#include <ice/Screen.h>
#include <ice/Engine.h>
#include <ice/GraphicSystem.h>
#include <ice/Rectangle.h>
#include <ice/Window.h>
#include <ice/Font.h>
#include <ice/Text.h>

#include "test_env.h"
#include "glm_checks.h"
#include "texture_checks.h"

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