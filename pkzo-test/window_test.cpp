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

TEST(Window, window_creation)
{
    auto event_router = pkzo::EventRouter{};
    auto size = glm::uvec2{800, 600};

    auto window = pkzo::Window{event_router, size, pkzo::WindowMode::STATIC, "Test Window"};
}

TEST(Window, window_get_set_size)
{
    auto event_router = pkzo::EventRouter{};
    auto size = glm::uvec2{800, 600};
    auto window = pkzo::Window{event_router, size, pkzo::WindowMode::STATIC, "Test Window"};

    auto actual_size = window.get_size();
    EXPECT_EQ(size.x, actual_size.x);
    EXPECT_EQ(size.y, actual_size.y);

    auto new_size = glm::uvec2{1024, 768};
    window.set_size(new_size);

    actual_size = window.get_size();
    EXPECT_EQ(new_size.x, actual_size.x);
    EXPECT_EQ(new_size.y, actual_size.y);
}

TEST(Window, window_mode_switch)
{
    auto event_router = pkzo::EventRouter{};
    auto size = glm::uvec2{800, 600};
    auto window = pkzo::Window{event_router, size, pkzo::WindowMode::STATIC, "Test Window"};

    EXPECT_EQ(window.get_mode(), pkzo::WindowMode::STATIC);

    window.set_mode(pkzo::WindowMode::FULLSCREEN);
    EXPECT_EQ(window.get_mode(), pkzo::WindowMode::FULLSCREEN);

    window.set_mode(pkzo::WindowMode::STATIC);
    EXPECT_EQ(window.get_mode(), pkzo::WindowMode::STATIC);
}

TEST(Window, window_get_set_title)
{
    auto event_router = pkzo::EventRouter{};
    auto size = glm::uvec2{800, 600};
    auto window = pkzo::Window{event_router, size, pkzo::WindowMode::STATIC, "Test Window"};

    EXPECT_EQ(window.get_title(), "Test Window");


    auto new_title = std::string{"New Title"};
    window.set_title(new_title);

    EXPECT_EQ(window.get_title(), new_title);
}
