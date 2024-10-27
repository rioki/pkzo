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

TEST(Keyboard, key_press_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto keyboard     = pkzo::Keyboard{event_router};

    auto expected_mod = pkzo::KeyMod::CTRL;
    auto expected_key = pkzo::Key::A;
    auto callback_called = false;

    keyboard.on_key_press([&](pkzo::KeyMod mod, pkzo::Key key) {
        callback_called = true;
        EXPECT_EQ(mod, expected_mod);
        EXPECT_EQ(key, expected_key);
    });

    event_router.inject_key_down(expected_mod, expected_key);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

TEST(Keyboard, key_release_event_triggers_signal)
{
    auto event_router = pkzo::EventRouter{};
    auto keyboard     = pkzo::Keyboard{event_router};

    auto expected_mod = pkzo::KeyMod::ALT;
    auto expected_key = pkzo::Key::B;
    auto callback_called = false;

    keyboard.on_key_release([&](pkzo::KeyMod mod, pkzo::Key key) {
        callback_called = true;
        EXPECT_EQ(mod, expected_mod);
        EXPECT_EQ(key, expected_key);
    });

    event_router.inject_key_up(expected_mod, expected_key);
    event_router.tick();

    EXPECT_TRUE(callback_called);
}

