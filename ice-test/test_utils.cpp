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