// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Engine.h>
#include <ice/GraphicSystem.h>
#include <ice/Window.h>
#include <ice/glm_json.h>

#include "test_utils.h"

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

    EXPECT_EQ(glm::uvec2(640, 480), window->get_size());
    EXPECT_EQ(ice::WindowMode::RESIZABLE, window->get_mode());
}
