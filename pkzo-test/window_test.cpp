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

#include "pch.h"

#include <SDL2/SDL_opengl.h>
#include <pkzo/Window.h>

glm::uvec2 get_desktop_size()
{
    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) != 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
    return {mode.w, mode.h};
}

TEST(Window, GRAPH_create)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {640, 480}, pkzo::WindowMode::WINDOWED};

    EXPECT_EQ(window.get_title(), "Test");
    EXPECT_EQ(window.get_size(), glm::uvec2(640, 480));
    EXPECT_EQ(window.get_window_mode(), pkzo::WindowMode::WINDOWED);
}

TEST(Window, GRAPH_create_simple)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {640, 480}};

    EXPECT_EQ(window.get_title(), "Test");
    EXPECT_EQ(window.get_size(), glm::uvec2(640, 480));
    EXPECT_EQ(window.get_window_mode(), pkzo::WindowMode::WINDOWED);
}

TEST(Window, GRAPH_create_fullscreen)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {640, 480}, pkzo::WindowMode::FULLSCREEN_DESKTOP};

    EXPECT_EQ(window.get_title(), "Test");
    EXPECT_EQ(window.get_size(), get_desktop_size());
    EXPECT_EQ(window.get_window_mode(), pkzo::WindowMode::FULLSCREEN_DESKTOP);
}

TEST(Window, GRAPH_resize)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {640, 480}, pkzo::WindowMode::WINDOWED};

    window.set_video_mode({800, 600}, pkzo::WindowMode::FULLSCREEN_DESKTOP);

    EXPECT_EQ(window.get_size(), get_desktop_size());
    EXPECT_EQ(window.get_window_mode(), pkzo::WindowMode::FULLSCREEN_DESKTOP);
}

TEST(Window, GRAPH_init_position)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {100, 101}, {640, 480}, pkzo::WindowMode::WINDOWED};

    EXPECT_EQ(window.get_position(), glm::ivec2(100, 101));
}

TEST(Window, GRAPH_use_gl_context)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Test", {640, 480}, pkzo::WindowMode::WINDOWED};

    window.on_draw([](){
        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}
