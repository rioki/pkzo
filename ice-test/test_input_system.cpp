// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Engine.h>
#include <ice/InputSystem.h>

#include "test_utils.h"

TEST(GraphicSystem, has_devices_after_load)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::InputSystem>();

    const auto* is = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, is);

    const auto* mouse = is->get_mouse();
    ASSERT_NE(nullptr, mouse);

    const auto* keyboard = is->get_keyboard();
    ASSERT_NE(nullptr, keyboard);

    auto js = is->get_joysticks();
    // if there are some, check if they are valid
    for (const auto& j : js)
    {
        ASSERT_NE(nullptr, j);
    }
}

