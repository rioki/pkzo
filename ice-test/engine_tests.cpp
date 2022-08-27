// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Engine.h>

#include "test_utils.h"

TEST(Engine, load_settings)
{
    auto engine = ice::Engine{};

    const auto& a = engine.get_settings();
    EXPECT_EQ("fallback", a.get_value("test", "greeting", "fallback"));

    engine.load_settings(ice::test::get_test_input() / "TestSettings.json");

    const auto& b = engine.get_settings();
    EXPECT_EQ("Hello World!", b.get_value("test", "greeting", "fallback"));

}