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

#include <gtest/gtest.h>

#include <SDL2/SDL_timer.h>
#include <pkzo/EventRouter.h>

TEST(EventRouter, construct)
{
    auto er = pkzo::EventRouter{};
}

TEST(EventRouter, route_event)
{
    auto er = pkzo::EventRouter{};

    {
        auto event = SDL_Event{SDL_MOUSEMOTION};
        event.motion.x          = 5;
        event.motion.y          = 4;
        event.motion.xrel       = 1;
        event.motion.yrel       = 2;
        event.motion.timestamp  = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    auto count = 0u;
    er.get_event_signal().connect([&] (auto event) {
        count++;
        EXPECT_EQ(SDL_MOUSEMOTION, event.type);
        EXPECT_EQ(5, event.motion.x);
        EXPECT_EQ(4, event.motion.y);
        EXPECT_EQ(1, event.motion.xrel);
        EXPECT_EQ(2, event.motion.yrel);
    });

    er.route_events();

    EXPECT_EQ(1, count);
}
