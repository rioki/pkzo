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

#include <ice/strex.h>

TEST(strex, narrow)
{
    EXPECT_EQ("Hello World", strex::narrow("Hello World"));
    EXPECT_EQ("Hello World", strex::narrow(L"Hello World"));
    EXPECT_EQ("Hello World", strex::narrow(u8"Hello World"));
    EXPECT_EQ("Hello World", strex::narrow(u"Hello World"));
    EXPECT_EQ("Hello World", strex::narrow(U"Hello World"));
}

TEST(strex, widen)
{
    EXPECT_EQ(L"Hello World", strex::widen("Hello World"));
    EXPECT_EQ(L"Hellö World", strex::widen(L"Hellö World"));
    EXPECT_EQ(L"Hellö World", strex::widen(u8"Hellö World"));
    EXPECT_EQ(L"Hellö World", strex::widen(u"Hellö World"));
    EXPECT_EQ(L"Hellö World", strex::widen(U"Hellö World"));
}

TEST(strex, utf8)
{
    EXPECT_EQ(u8"Hello World", strex::utf8("Hello World"));
    EXPECT_EQ(u8"Hellö World", strex::utf8(L"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strex::utf8(u8"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strex::utf8(u"Hellö World"));
    EXPECT_EQ(u8"Hellö World", strex::utf8(U"Hellö World"));
}

TEST(strex, utf16)
{
    EXPECT_EQ(u"Hello World", strex::utf16("Hello World"));
    EXPECT_EQ(u"Hellö World", strex::utf16(L"Hellö World"));
    EXPECT_EQ(u"Hellö World", strex::utf16(u8"Hellö World"));
    EXPECT_EQ(u"Hellö World", strex::utf16(u"Hellö World"));
    EXPECT_EQ(u"Hellö World", strex::utf16(U"Hellö World"));
}

TEST(strex, utf32)
{
    EXPECT_EQ(U"Hello World", strex::utf32("Hello World"));
    EXPECT_EQ(U"Hellö World", strex::utf32(L"Hellö World"));
    EXPECT_EQ(U"Hellö World", strex::utf32(u8"Hellö World"));
    EXPECT_EQ(U"Hellö World", strex::utf32(u"Hellö World"));
    EXPECT_EQ(U"Hellö World", strex::utf32(U"Hellö World"));
}
