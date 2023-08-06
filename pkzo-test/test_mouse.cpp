// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include <pkzo/Mouse.h>

#include <pkzo/EventRouter.h>

#include <gtest/gtest.h>

TEST(Mouse, construct)
{
    auto router = pkzo::EventRouter{};
    auto mouse  = pkzo::Mouse{router};
}

TEST(Mouse, handle_buttons)
{
    auto router = pkzo::EventRouter{};
    auto mouse  = pkzo::Mouse{router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto pos     = glm::ivec2(0);
    auto pressed = false;

    mouse.get_button_press_signal().connect([&] (auto _button, auto _pos) {
        count++;
        button  = _button;
        pos     = _pos;
        pressed = true;
    });
    mouse.get_button_release_signal().connect([&] (auto _button, auto _pos) {
        count++;
        button  = _button;
        pos     = _pos;
        pressed = false;
    });

    router.inject_mouse_button_press(pkzo::MouseButton::LEFT, {1,2});
    router.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(pkzo::MouseButton::LEFT, button);
    EXPECT_EQ(glm::ivec2(1,2),         pos);
    EXPECT_TRUE(pressed);

    router.inject_mouse_button_release(pkzo::MouseButton::RIGHT, {3,4});;
    router.route_events();

    EXPECT_EQ(2,                 count);
    EXPECT_EQ(pkzo::MouseButton::RIGHT, button);
    EXPECT_EQ(glm::ivec2(3,4),         pos);
    EXPECT_FALSE(pressed);
}

TEST(Mouse, handle_movement)
{
    auto router = pkzo::EventRouter{};
    auto mouse  = pkzo::Mouse{router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto pos     = glm::ivec2(0);
    auto rel     = glm::ivec2(0);
    auto pressed = false;

    mouse.get_move_signal().connect([&] (auto _pos, auto _rel) {
        count++;
        pos     = _pos;
        rel     = _rel;
        pressed = true;
    });

    router.inject_mouse_move({4,5}, {-1,2});
    router.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(glm::ivec2(4,5), pos);
    EXPECT_EQ(glm::ivec2(-1,2), rel);
    EXPECT_TRUE(pressed);
}

TEST(Mouse, handle_wheel)
{
    auto router = pkzo::EventRouter{};
    auto mouse  = pkzo::Mouse{router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto rel     = glm::ivec2(0);
    auto pressed = false;

    mouse.get_wheel_signal().connect([&] (auto _rel) {
        count++;
        rel     = _rel;
        pressed = true;
    });

    router.inject_mouse_wheel({-1,2});
    router.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(glm::ivec2(-1,2), rel);
    EXPECT_TRUE(pressed);
}
