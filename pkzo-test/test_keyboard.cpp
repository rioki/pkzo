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

#include <pkzo/Keyboard.h>

#include <pkzo/EventRouter.h>

#include <gtest/gtest.h>

TEST(Keyboard, construct)
{
    auto er = pkzo::EventRouter{};
    auto kb = pkzo::Keyboard{er};
}

TEST(Keyboard, handle_keys)
{
    auto er = pkzo::EventRouter{};
    auto kb = pkzo::Keyboard{er};

    auto count   = 0u;
    auto mod     = pkzo::KeyMod::NONE;
    auto key     = pkzo::Key::UNKNOWN;
    auto pressed = false;

    kb.get_key_press_signal().connect([&] (auto _mod, auto _key) {
        count++;
        mod = _mod;
        key = _key;
        pressed = true;
    });
    kb.get_key_release_signal().connect([&] (auto _mod, auto _key) {
        count++;
        mod = _mod;
        key = _key;
        pressed = false;
    });

    er.inject_key_press(pkzo::KeyMod::CTRL, pkzo::Key::C);
    er.route_events();

    EXPECT_EQ(1, count);
    EXPECT_EQ(pkzo::KeyMod::CTRL, mod);
    EXPECT_EQ(pkzo::Key::C,       key);
    EXPECT_TRUE(pressed);

    er.inject_key_release(pkzo::KeyMod::ALT, pkzo::Key::V);
    er.route_events();

    EXPECT_EQ(2,                 count);
    EXPECT_EQ(pkzo::KeyMod::ALT, mod);
    EXPECT_EQ(pkzo::Key::V,      key);
    EXPECT_FALSE(pressed);
}
