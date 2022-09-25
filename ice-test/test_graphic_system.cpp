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

TEST(GraphicSystem, has_window_after_load)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::SdlGraphicSystem>();

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

    engine.start_system<ice::SdlGraphicSystem>();

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

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);

    engine.start_system<ice::SdlGraphicSystem>();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);

    engine.tick(); // not sure why, but let the engine run at least once

    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);

}
