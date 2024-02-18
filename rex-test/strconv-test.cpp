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
    EXPECT_EQ(L"Hellö World", rex::widen(L"Hellö World"));
    EXPECT_EQ(L"Hellö World", rex::widen(u8"Hellö World"));
    EXPECT_EQ(L"Hellö World", rex::widen(u"Hellö World"));
    EXPECT_EQ(L"Hellö World", rex::widen(U"Hellö World"));
}

TEST(strconv, utf8)
{
    EXPECT_EQ(u8"Hello World", rex::utf8("Hello World"));
    EXPECT_EQ(u8"Hellö World", rex::utf8(L"Hellö World"));
    EXPECT_EQ(u8"Hellö World", rex::utf8(u8"Hellö World"));
    EXPECT_EQ(u8"Hellö World", rex::utf8(u"Hellö World"));
    EXPECT_EQ(u8"Hellö World", rex::utf8(U"Hellö World"));
}

TEST(strconv, utf16)
{
    EXPECT_EQ(u"Hello World", rex::utf16("Hello World"));
    EXPECT_EQ(u"Hellö World", rex::utf16(L"Hellö World"));
    EXPECT_EQ(u"Hellö World", rex::utf16(u8"Hellö World"));
    EXPECT_EQ(u"Hellö World", rex::utf16(u"Hellö World"));
    EXPECT_EQ(u"Hellö World", rex::utf16(U"Hellö World"));
}

TEST(strconv, utf32)
{
    EXPECT_EQ(U"Hello World", rex::utf32("Hello World"));
    EXPECT_EQ(U"Hellö World", rex::utf32(L"Hellö World"));
    EXPECT_EQ(U"Hellö World", rex::utf32(u8"Hellö World"));
    EXPECT_EQ(U"Hellö World", rex::utf32(u"Hellö World"));
    EXPECT_EQ(U"Hellö World", rex::utf32(U"Hellö World"));
}
