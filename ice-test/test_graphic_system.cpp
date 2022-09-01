// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Engine.h>
#include <ice/GraphicSystem.h>
#include <ice/Window.h>
#include <ice/glm_json.h>

#include "test_env.h"
#include "glm_checks.h"
#include "texture_checks.h"

TEST(GraphicSystem, has_window_after_load)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::GraphicSystem>();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);

    const auto* window = gs->get_window();
    ASSERT_NE(nullptr, window);
}

TEST(GraphicSystem, uses_settings)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(640, 480));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::RESIZABLE);

    engine.start_system<ice::GraphicSystem>();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);

    const auto* window = gs->get_window();
    ASSERT_NE(nullptr, window);

    EXPECT_GLM_EQ(glm::uvec2(640, 480), window->get_size());
    EXPECT_EQ(ice::WindowMode::RESIZABLE, window->get_mode());
}

TEST(GraphicSystem, empty_screeshot)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::GraphicSystem>();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);

    engine.tick(); // not sure why, but let the engine run at least once

    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);

}
