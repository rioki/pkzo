// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <pkzo/pkzo.h>
#include <gtest/gtest.h>

TEST(Mouse, button_press_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto expected_position = glm::uvec2(100, 200);
    auto expected_button   = pkzo::MouseButton::LEFT;
    auto callback_called   = false;

    mouse.on_button_press([&](glm::uvec2 position, pkzo::MouseButton button) {
        callback_called = true;
        EXPECT_EQ(position, expected_position);
        EXPECT_EQ(button, expected_button);
    });

    event_router.inject_button_press(expected_position, expected_button);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

TEST(Mouse, button_release_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto expected_position = glm::uvec2(150, 250);
    auto expected_button   = pkzo::MouseButton::RIGHT;
    auto callback_called   = false;

    mouse.on_button_release([&](glm::uvec2 position, pkzo::MouseButton button) {
        callback_called = true;
        EXPECT_EQ(position, expected_position);
        EXPECT_EQ(button, expected_button);
    });

    event_router.inject_button_release(expected_position, expected_button);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

TEST(Mouse, move_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto expected_position = glm::uvec2(200, 300);
    auto expected_delta    = glm::ivec2(10, 15);
    auto callback_called   = false;

    mouse.on_move([&](glm::uvec2 position, glm::ivec2 delta) {
        callback_called = true;
        EXPECT_EQ(position, expected_position);
        EXPECT_EQ(delta, expected_delta);
    });

    event_router.inject_mouse_move(expected_position, expected_delta);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

TEST(Mouse, wheel_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto expected_scroll = glm::ivec2(0, -1);
    auto callback_called = false;

    mouse.on_wheel([&](glm::ivec2 scroll) {
        callback_called = true;
        EXPECT_EQ(scroll, expected_scroll);
    });

    event_router.inject_mouse_wheel(expected_scroll);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

TEST(Mouse, set_and_get_cursor_visibility)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    mouse.set_cursor_visible(false);
    EXPECT_FALSE(mouse.get_cursor_visible());

    mouse.set_cursor_visible(true);
    EXPECT_TRUE(mouse.get_cursor_visible());
}
