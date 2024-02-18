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

#include "pch.h"

#include <pkzo/HitArea.h>
#include <pkzo/Screen.h>
#include <pkzo/EventRouter.h>
#include <pkzo/Window.h>

TEST(HitAreaTest, GRAPH_clicks)
{
    auto er     = pkzo::EventRouter{};
    auto window = pkzo::Window{er, testing::get_test_name(), {800u, 600u}};

    auto screen = pkzo::Screen{{800u, 600u}};

    auto transform = glm::translate(glm::mat3(1.0f), glm::vec2{200, 150});
    auto hit_area = pkzo::HitArea{transform, {250, 300}};
    auto click_count = 0u;
    hit_area.on_click([&]()
    {
        click_count++;
    });
    screen.add_node(hit_area);

    screen.activate();

    // down in ; up in -> click
    screen.handle_mouse_button_down(pkzo::MouseButton::LEFT, {250, 300});
    EXPECT_EQ(click_count, 0);
    screen.handle_mouse_button_up(pkzo::MouseButton::LEFT, {250, 300});
    EXPECT_EQ(click_count, 1);

    // down out ; up out -> no click
    screen.handle_mouse_button_down(pkzo::MouseButton::LEFT, {100, 100});
    EXPECT_EQ(click_count, 1);
    screen.handle_mouse_button_up(pkzo::MouseButton::LEFT, {100, 100});
    EXPECT_EQ(click_count, 1);

    // down in ; up out -> no click
    screen.handle_mouse_button_down(pkzo::MouseButton::LEFT, {250, 300});
    EXPECT_EQ(click_count, 1);
    screen.handle_mouse_button_up(pkzo::MouseButton::LEFT, {100, 100});
    EXPECT_EQ(click_count, 1);

    // down out ; up in -> no click
    screen.handle_mouse_button_down(pkzo::MouseButton::LEFT, {100, 100});
    EXPECT_EQ(click_count, 1);
    screen.handle_mouse_button_up(pkzo::MouseButton::LEFT, {250, 300});
    EXPECT_EQ(click_count, 1);
}