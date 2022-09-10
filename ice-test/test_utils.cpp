// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"

#include <ice/ice.h>

TEST(utils, utf32)
{
    using namespace std::literals::string_literals;

    EXPECT_EQ(U"Hal�le"s, ice::utf32(u8"Hal�le"s));
    EXPECT_EQ(U"Hello"s,  ice::utf32("Hello"s));
}

TEST(utils, join)
{
    EXPECT_EQ("1,2,3,4,5", ice::join({"1", "2", "3", "4", "5"}, ","));
}

TEST(utils, explode)
{
    EXPECT_EQ(std::vector<std::string>({"1", "2", "3", "4", "5"}), ice::explode("1,2,3,4,5", ","));
    EXPECT_EQ(std::vector<std::string>({"1", "2", "", "3", "4", "5"}), ice::explode("1,2,,3,4,5", ","));
}

TEST(utils, tokenize)
{
    EXPECT_EQ(std::vector<std::string>(), ice::tokenize(""));
    EXPECT_EQ(std::vector<std::string>({"one"}), ice::tokenize("one"));
    EXPECT_EQ(std::vector<std::string>({"one", "two", "three"}), ice::tokenize("one two three"));
    EXPECT_EQ(std::vector<std::string>({"one", "=", "two", "+", "three"}), ice::tokenize("one = two + three"));
    EXPECT_EQ(std::vector<std::string>({"a", "=", "1", "+", "2"}), ice::tokenize("a = 1 + 2"));
    EXPECT_EQ(std::vector<std::string>({"a", "=", "1", "+", "2"}), ice::tokenize("a=1+2"));
    EXPECT_EQ(std::vector<std::string>({"greeting", "=", "Hello World!"}), ice::tokenize("greeting = \"Hello World!\""));
    EXPECT_EQ(std::vector<std::string>({"greeting", "=", "Hello \"World\"!"}), ice::tokenize("greeting = \"Hello \\\"World\\\"!\""));
}