// rioki's C++ extentions
// Copyright 2021-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include <rex/managed_ptr.h>

class AllocTester
{
public:
    static unsigned int count;

    AllocTester()
    {
        count++;
    }

    ~AllocTester()
    {
        count--;
    }

private:
    AllocTester(const AllocTester&) = delete;
    AllocTester& operator = (const AllocTester&) = delete;
};

unsigned int AllocTester::count = 0;

TEST(managed_ptr, default_ctor)
{
    rex::managed_ptr<int> p;
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_TRUE(p == nullptr);
    EXPECT_FALSE(p);
}

TEST(managed_ptr, make_managed)
{
    auto p = rex::make_managed<int>(42);
    EXPECT_NE(p.get(), nullptr);
    EXPECT_TRUE(p != nullptr);
    EXPECT_TRUE(p);
    EXPECT_TRUE(p.is_managed());
    EXPECT_EQ(42, *p);
}

TEST(managed_ptr, wrap_managed)
{
    auto v = 42;
    auto p = rex::wrap_managed<int>(v);
    EXPECT_NE(p.get(), nullptr);
    EXPECT_TRUE(p != nullptr);
    EXPECT_TRUE(p);
    EXPECT_FALSE(p.is_managed());
    EXPECT_EQ(42, *p);
}

TEST(managed_ptr, wrap_managed_ptr)
{
    auto v = 42;
    auto p = rex::wrap_managed<int>(&v);
    EXPECT_NE(p.get(), nullptr);
    EXPECT_TRUE(p != nullptr);
    EXPECT_TRUE(p);
    EXPECT_FALSE(p.is_managed());
    EXPECT_EQ(42, *p);
}

TEST(managed_ptr, make_managed_deletes)
{
    AllocTester::count = 0;
    {
        auto p = rex::make_managed<AllocTester>();
        EXPECT_EQ(1, AllocTester::count);
    }
    EXPECT_EQ(0, AllocTester::count);
}

TEST(managed_ptr, wrap_managed_does_not_delete)
{
    AllocTester::count = 0;
    AllocTester* ac = new AllocTester();
    {
        auto p = rex::wrap_managed(ac);
        EXPECT_EQ(1, AllocTester::count);
    }
    ASSERT_EQ(1, AllocTester::count);
    delete ac;
}

TEST(managed_ptr, move_onto)
{
    AllocTester::count = 0;
    {
        auto p = rex::make_managed<AllocTester>();
        EXPECT_EQ(1, AllocTester::count);

        auto p2 = std::move(p);
        EXPECT_EQ(1, AllocTester::count);
    }
    EXPECT_EQ(0, AllocTester::count);
}

TEST(managed_ptr, make_unique)
{
    AllocTester::count = 0;
    {
        rex::managed_ptr<AllocTester> p = std::make_unique<AllocTester>();
        EXPECT_EQ(1, AllocTester::count);
    }
    EXPECT_EQ(0, AllocTester::count);
}
