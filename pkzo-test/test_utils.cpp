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


#include <pkzo/utils.h>

#include <gtest/gtest.h>

#include "pkzo_test.h"

TEST(utils, load_binary_file)
{
    auto texture = pkzo::load_binary_file(pkzo::test::get_test_input() / "AngryCat.jpg");
    EXPECT_EQ(std::byte(0xFF), texture[0]);
    EXPECT_EQ(std::byte(0xD8), texture[1]);
    EXPECT_EQ(std::byte(0xFF), texture[2]);
    EXPECT_EQ(std::byte(0xE0), texture[3]);

    EXPECT_EQ(std::byte('J'), texture[6]);
    EXPECT_EQ(std::byte('F'), texture[7]);
    EXPECT_EQ(std::byte('I'), texture[8]);
    EXPECT_EQ(std::byte('F'), texture[9]);
}

TEST(utils, load_text_file)
{
    auto text = pkzo::load_text_file(pkzo::test::get_test_input() / "empty.json");
    EXPECT_EQ("{}", text);
}