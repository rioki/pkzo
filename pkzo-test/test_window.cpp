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

#include <pkzo/Window.h>

#include <pkzo/EventRouter.h>

#include <gtest/gtest.h>
#include "glm_gtest.h"
#include "pkzo_test.h"

TEST(Window, GRAPH_create_windowed)
{
    auto window = pkzo::Window{{800,600}, "Test"};

    EXPECT_GLM_EQ(glm::uvec2(800, 600), window.get_size());
    EXPECT_EQ("Test", window.get_caption());
}

TEST(Window, GRAPH_create_fullscreen)
{
    auto window = pkzo::Window{pkzo::fullscreen, "Test"};

    EXPECT_GLM_NE(glm::uvec2(800, 600), window.get_size());
    EXPECT_EQ("Test", window.get_caption());
}

TEST(Window, GRAPH_resize_windowed)
{
    auto router = pkzo::EventRouter{};
    auto window = pkzo::Window{router, {800,600}, "Test"};

    EXPECT_GLM_EQ(glm::uvec2(800, 600), window.get_size());
    EXPECT_EQ("Test", window.get_caption());

    auto count = 0u;
    auto size  = glm::uvec2{0u, 0u};
    window.get_resize_signal().connect([&] (auto new_size) {
        count++;
        size = new_size;
    });

    router.inject_window_resize({801,599});
    router.route_events();

}

TEST(Window, GRAPH_resize_fullscreen)
{
    auto router = pkzo::EventRouter{};
    auto window = pkzo::Window{router, pkzo::fullscreen, "Test"};

    EXPECT_GLM_NE(glm::uvec2(800, 600), window.get_size());
    EXPECT_EQ("Test", window.get_caption());
}

TEST(Window, GRAPH_save_screenshot)
{
    auto window = pkzo::Window{{800,600}, "Test"};

    window.draw();

    auto screenshot = window.save_screen();
    EXPECT_GLM_EQ(glm::uvec2(800, 600), screenshot->get_size());
    EXPECT_TEXTURE_REF_EQ(screenshot);
}
