//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"

TEST(Main, open_window)
{
    pkzo::Main main;
    auto& window = main.open_window({800, 600}, pkzo::WindowMode::STATIC, "open_window");
    EXPECT_EQ(pkzo::WindowMode::STATIC, window.get_mode());
    EXPECT_EQ(glm::uvec2(800, 600), window.get_size());
    EXPECT_EQ("open_window", window.get_caption());
}

TEST(Main, on_handlers_can_disconnect)
{
    pkzo::Main main;

    auto tick_con = main.on_tick([] (auto dt) {});
    EXPECT_NO_THROW(main.get_tick_signal().disconnect(tick_con));

    auto quit_con = main.on_quit([] () {});
    EXPECT_NO_THROW(main.get_quit_signal().disconnect(quit_con));
}