// strconv - string conversion utilities
// Copyright 2022-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include <rex/strconv.h>

TEST(strconv, narrow)
{
    EXPECT_EQ("Hello World", rex::narrow("Hello World"));
    EXPECT_EQ("Hello World", rex::narrow(L"Hello World"));
    EXPECT_EQ("Hello World", rex::narrow(u8"Hello World"));
    EXPECT_EQ("Hello World", rex::narrow(u"Hello World"));
    EXPECT_EQ("Hello World", rex::narrow(U"Hello World"));
}

TEST(strconv, widen)
{
    EXPECT_EQ(L"Hello World", rex::widen("Hello World"));
    EXPECT_EQ(L"Hell� World", rex::widen(L"Hell� World"));
    EXPECT_EQ(L"Hell� World", rex::widen(u8"Hell� World"));
    EXPECT_EQ(L"Hell� World", rex::widen(u"Hell� World"));
    EXPECT_EQ(L"Hell� World", rex::widen(U"Hell� World"));
}

TEST(strconv, utf8)
{
    EXPECT_EQ(u8"Hello World", rex::utf8("Hello World"));
    EXPECT_EQ(u8"Hell� World", rex::utf8(L"Hell� World"));
    EXPECT_EQ(u8"Hell� World", rex::utf8(u8"Hell� World"));
    EXPECT_EQ(u8"Hell� World", rex::utf8(u"Hell� World"));
    EXPECT_EQ(u8"Hell� World", rex::utf8(U"Hell� World"));
}

TEST(strconv, utf16)
{
    EXPECT_EQ(u"Hello World", rex::utf16("Hello World"));
    EXPECT_EQ(u"Hell� World", rex::utf16(L"Hell� World"));
    EXPECT_EQ(u"Hell� World", rex::utf16(u8"Hell� World"));
    EXPECT_EQ(u"Hell� World", rex::utf16(u"Hell� World"));
    EXPECT_EQ(u"Hell� World", rex::utf16(U"Hell� World"));
}

TEST(strconv, utf32)
{
    EXPECT_EQ(U"Hello World", rex::utf32("Hello World"));
    EXPECT_EQ(U"Hell� World", rex::utf32(L"Hell� World"));
    EXPECT_EQ(U"Hell� World", rex::utf32(u8"Hell� World"));
    EXPECT_EQ(U"Hell� World", rex::utf32(u"Hell� World"));
    EXPECT_EQ(U"Hell� World", rex::utf32(U"Hell� World"));
}
