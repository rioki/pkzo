// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/ice.h>

TEST(utils, utf32)
{
    using namespace std::literals::string_literals;

    EXPECT_EQ(U"Halöle"s, ice::utf32(u8"Halöle"s));
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