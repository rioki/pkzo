// strconv - string conversion utilities
// Copyright 2022-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include <pkzo/strconv.h>

#include <gtest/gtest.h>

TEST(strconv, narrow)
{
    EXPECT_EQ("Hello World", strconv::narrow("Hello World"));
    EXPECT_EQ("Hello World", strconv::narrow(L"Hello World"));
    EXPECT_EQ("Hello World", strconv::narrow(u8"Hello World"));
    EXPECT_EQ("Hello World", strconv::narrow(u"Hello World"));
    EXPECT_EQ("Hello World", strconv::narrow(U"Hello World"));
}

TEST(strconv, widen)
{
    EXPECT_EQ(L"Hello World", strconv::widen("Hello World"));
    EXPECT_EQ(L"Hellö World", strconv::widen(L"Hellö World"));
    EXPECT_EQ(L"Hellö World", strconv::widen(u8"Hellö World"));
    EXPECT_EQ(L"Hellö World", strconv::widen(u"Hellö World"));
    EXPECT_EQ(L"Hellö World", strconv::widen(U"Hellö World"));
}

TEST(strconv, utf8)
{
    EXPECT_EQ(u8"Hello World", strconv::utf8("Hello World"));
    EXPECT_EQ(u8"Hellö World", strconv::utf8(L"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strconv::utf8(u8"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strconv::utf8(u"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strconv::utf8(U"Hellö World"));
}

TEST(strconv, utf16)
{
    EXPECT_EQ(u"Hello World", strconv::utf16("Hello World"));
    EXPECT_EQ(u"Hellö World", strconv::utf16(L"Hellö World"));
    EXPECT_EQ(u"Hellö World", strconv::utf16(u8"Hellö World"));
    EXPECT_EQ(u"Hellö World", strconv::utf16(u"Hellö World"));
    EXPECT_EQ(u"Hellö World", strconv::utf16(U"Hellö World"));
}

TEST(strconv, utf32)
{
    EXPECT_EQ(U"Hello World", strconv::utf32("Hello World"));
    EXPECT_EQ(U"Hellö World", strconv::utf32(L"Hellö World"));
    EXPECT_EQ(U"Hellö World", strconv::utf32(u8"Hellö World"));
    EXPECT_EQ(U"Hellö World", strconv::utf32(u"Hellö World"));
    EXPECT_EQ(U"Hellö World", strconv::utf32(U"Hellö World"));
}
