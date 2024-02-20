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

#include <pkzo/Keyboard.h>
#include <pkzo/EventRouter.h>

TEST(Keyboard, handle_keys)
{
    auto event_router = pkzo::EventRouter{};
    auto kb = pkzo::Keyboard{event_router};

    auto count   = 0u;
    auto mod     = pkzo::KeyMod::NONE;
    auto key     = pkzo::Key::UNKNOWN;
    auto pressed = false;

    kb.on_key_press([&] (auto _mod, auto _key) {
        count++;
        mod = _mod;
        key = _key;
        pressed = true;
    });
    kb.on_key_release([&] (auto _mod, auto _key) {
        count++;
        mod = _mod;
        key = _key;
        pressed = false;
    });

    auto event1 = SDL_Event{SDL_KEYDOWN};
    event1.key.keysym.mod      = KMOD_LCTRL;
    event1.key.keysym.scancode = SDL_SCANCODE_C;
    event1.key.keysym.sym      = SDL_GetKeyFromScancode(event1.key.keysym.scancode);
    event1.key.timestamp       = SDL_GetTicks();
    SDL_PushEvent(&event1);

    event_router.route_events();

    EXPECT_EQ(1,                   count);
    EXPECT_EQ(pkzo::KeyMod::LCTRL, mod);
    EXPECT_EQ(pkzo::Key::C,        key);
    EXPECT_TRUE(pressed);

    auto event2 = SDL_Event{SDL_KEYUP};
    event2.key.keysym.mod      = KMOD_LALT;
    event2.key.keysym.scancode = SDL_SCANCODE_V;
    event2.key.keysym.sym      = SDL_GetKeyFromScancode(event2.key.keysym.scancode);
    event2.key.timestamp       = SDL_GetTicks();

    SDL_PushEvent(&event2);

    event_router.route_events();

    EXPECT_EQ(2,                  count);
    EXPECT_EQ(pkzo::KeyMod::LALT, mod);
    EXPECT_EQ(pkzo::Key::V,       key);
    EXPECT_FALSE(pressed);
}