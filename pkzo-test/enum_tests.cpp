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

TEST(enums, keymod_bitweise_or)
{
    auto mod = pkzo::KeyMod::SHIFT | pkzo::KeyMod::CTRL;
    EXPECT_EQ(mod, static_cast<pkzo::KeyMod>(KMOD_SHIFT | KMOD_CTRL));
}

TEST(enums, keymod_bitweise_and)
{
    auto mod = pkzo::KeyMod::SHIFT | pkzo::KeyMod::CTRL;
    EXPECT_EQ(mod & pkzo::KeyMod::SHIFT, pkzo::KeyMod::SHIFT);
    EXPECT_EQ(mod & pkzo::KeyMod::ALT, pkzo::KeyMod::NONE);
}

TEST(enums, keymod_bitweise_xor)
{
    auto mod = pkzo::KeyMod::SHIFT ^ pkzo::KeyMod::CTRL;
    EXPECT_EQ(mod, static_cast<pkzo::KeyMod>(KMOD_SHIFT ^ KMOD_CTRL));
}

TEST(enums, keymod_bitweise_not)
{
    auto mod = ~pkzo::KeyMod::SHIFT;
    EXPECT_EQ(mod & pkzo::KeyMod::SHIFT, pkzo::KeyMod::NONE);
}

TEST(enums, keymod_key_to_string)
{
    auto oss = std::ostringstream{};
    oss << pkzo::Key::A;
    EXPECT_EQ(oss.str(), "A");

    oss.str("");
    oss << pkzo::Key::UNKNOWN;
    EXPECT_EQ(oss.str(), "UNKNOWN");
}

TEST(enums, keymod_to_string)
{
    auto oss = std::ostringstream{};
    oss << (pkzo::KeyMod::CTRL | pkzo::KeyMod::SHIFT);
    EXPECT_EQ(oss.str(), "SHIFT|CTRL");

    oss.str("");
    oss << pkzo::KeyMod::NONE;
    EXPECT_EQ(oss.str(), "NONE");
}

TEST(enums, keymod_single_to_string)
{
    auto oss = std::ostringstream{};
    oss << pkzo::KeyMod::ALT;
    EXPECT_EQ(oss.str(), "ALT");
}