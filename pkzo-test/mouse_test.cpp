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

#include <pkzo/Mouse.h>
#include <pkzo/EventRouter.h>

TEST(Mouse, handle_buttons)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto pos     = glm::ivec2(0);
    auto pressed = false;

    mouse.on_button_press([&] (auto _button, auto _pos) {
        count++;
        button  = _button;
        pos     = _pos;
        pressed = true;
    });
    mouse.on_button_release([&] (auto _button, auto _pos) {
        count++;
        button  = _button;
        pos     = _pos;
        pressed = false;
    });

    auto event1 = SDL_Event{SDL_MOUSEBUTTONDOWN};
    event1.button.button       = SDL_BUTTON_LEFT;
    event1.button.x            = 1;
    event1.button.y            = 2;
    event1.button.timestamp    = SDL_GetTicks();
    SDL_PushEvent(&event1);

    event_router.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(pkzo::MouseButton::LEFT, button);
    EXPECT_EQ(glm::ivec2(1,2),         pos);
    EXPECT_TRUE(pressed);

    auto event2 = SDL_Event{SDL_MOUSEBUTTONUP};
    event2.button.button       = SDL_BUTTON_RIGHT;
    event2.button.x            = 3;
    event2.button.y            = 4;
    event2.button.timestamp    = SDL_GetTicks();
    SDL_PushEvent(&event2);

    event_router.route_events();

    EXPECT_EQ(2,                 count);
    EXPECT_EQ(pkzo::MouseButton::RIGHT, button);
    EXPECT_EQ(glm::ivec2(3,4),         pos);
    EXPECT_FALSE(pressed);
}

TEST(Mouse, handle_movement)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto pos     = glm::ivec2(0);
    auto rel     = glm::ivec2(0);
    auto pressed = false;

    mouse.on_move([&] (auto _pos, auto _rel) {
        count++;
        pos     = _pos;
        rel     = _rel;
        pressed = true;
    });

    auto event = SDL_Event{SDL_MOUSEMOTION};
    event.motion.x            = 4;
    event.motion.y            = 5;
    event.motion.xrel         = -1;
    event.motion.yrel         = 2;
    event.button.timestamp    = SDL_GetTicks();
    SDL_PushEvent(&event);

    event_router.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(glm::ivec2(4,5), pos);
    EXPECT_EQ(glm::ivec2(-1,2), rel);
    EXPECT_TRUE(pressed);
}

TEST(Mouse, handle_wheel)
{
    auto event_router = pkzo::EventRouter{};
    auto mouse        = pkzo::Mouse{event_router};

    auto count   = 0u;
    auto button  = pkzo::MouseButton::NONE;
    auto rel     = glm::ivec2(0);
    auto pressed = false;

    mouse.on_wheel([&] (auto _rel) {
        count++;
        rel     = _rel;
        pressed = true;
    });

    auto event = SDL_Event{SDL_MOUSEWHEEL};
    event.wheel.x          = -1;
    event.wheel.y          = 2;
    event.button.timestamp = SDL_GetTicks();
    SDL_PushEvent(&event);

    event_router.route_events();


    EXPECT_EQ(1, count);
    EXPECT_EQ(glm::ivec2(-1,2), rel);
    EXPECT_TRUE(pressed);
}
