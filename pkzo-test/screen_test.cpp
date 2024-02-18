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

#include <pkzo/color.h>
#include <pkzo/Screen.h>
#include <pkzo/Rectangle.h>
#include <pkzo/Image.h>
#include <pkzo/Font.h>
#include <pkzo/Text.h>

#include <pkzo/EventRouter.h>
#include <pkzo/Window.h>

using namespace testing;

TEST(Screen, create)
{
    auto screen = pkzo::Screen{{800u, 600u}};

    EXPECT_GLM_EQ(screen.get_size(), glm::uvec2(800, 600));
}

TEST(Screen, resize)
{
    auto screen = pkzo::Screen{{800u, 600u}};

    screen.resize({1024u, 768u});

    EXPECT_GLM_EQ(screen.get_size(), glm::uvec2(1024, 768));
}

TEST(Screen, render_empty)
{
    auto er     = pkzo::EventRouter{};
    auto window = pkzo::Window{er, get_test_name(), {800u, 600u}};

    auto screen = pkzo::Screen{window.get_drawable_size()};
    screen.set_background_color(pkzo::rgba(0x212121FF));

    window.on_draw([&] () {
        screen.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}

TEST(Screen, render_orange_rectnagle)
{
    auto er     = pkzo::EventRouter{};
    auto window = pkzo::Window{er, get_test_name(), {800u, 600u}};

    auto screen = pkzo::Screen{window.get_drawable_size()};
    screen.set_background_color(pkzo::rgba(0x212121FF));

    auto transform = glm::translate(glm::mat3(1.0f), glm::vec2{200, 150});
    auto rectnagle = pkzo::Rectangle{transform, {400u, 300u}, pkzo::rgba(0xFFA500FF)};
    screen.add_node(rectnagle);

    window.on_draw([&] () {
        screen.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}

TEST(Screen, render_angley_cat)
{
    auto er     = pkzo::EventRouter{};
    auto window = pkzo::Window{er, get_test_name(), {800u, 600u}};

    auto screen = pkzo::Screen{window.get_drawable_size()};
    screen.set_background_color(pkzo::rgba(0x212121FF));

    auto cat = std::make_shared<pkzo::Image>(testing::get_test_input() / "textures/AngryCat.png");

    auto transform = glm::translate(glm::mat3(1.0f), glm::vec2{200, 150});
    auto rectnagle = pkzo::Rectangle{transform, {400u, 300u}, pkzo::rgba(0xFFC0CBFF), cat};
    screen.add_node(rectnagle);

    window.on_draw([&] () {
        screen.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}

TEST(Screen, render_text)
{
    auto er     = pkzo::EventRouter{};
    auto window = pkzo::Window{er, get_test_name(), {800u, 600u}};

    auto screen = pkzo::Screen{window.get_drawable_size()};
    screen.set_background_color(pkzo::rgba(0x212121FF));

    auto font = std::make_shared<pkzo::Font>(testing::get_test_input() / "fonts/DejaVuSerif.ttf", 24);
    auto transform = glm::translate(glm::mat3(1.0f), glm::vec2{200, 150});
    auto text = pkzo::Text{transform, u8"The quick brown fox jumps over the lazy dog", font, pkzo::rgba(0xFFFFFFFF)};
    screen.add_node(text);

    window.on_draw([&] () {
        screen.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}
