// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include <rex/debug.h>
#include <rex/env.h>

TEST(debug, traces)
{
    auto count = 0u;
    auto old_trace_handler = rex::set_trace_handler([&](const std::string_view& message)
    {
        count++;
    });

    rex::trace("Hello World");

    EXPECT_EQ(count, 1u);

    rex::set_trace_handler(old_trace_handler);
}

TEST(debug, check_fails)
{
    auto count = 0u;
    auto old_fail_handler = rex::set_fail_handler([&]()
    {
        count++;
    });

    rex::check(true);
    rex::check(false);

    EXPECT_EQ(count, 1u);

    rex::set_fail_handler(old_fail_handler);
}

TEST(debug, check_traces)
{
    auto message = std::string{};
    auto old_trace_handler = rex::set_trace_handler([&](const std::string_view& m)
    {
        message = m;
    });
    auto old_fail_handler = rex::set_fail_handler([&]()
    {
        // do nothing
    });

    rex::check(false);

    auto source_location = std::source_location::current();
    auto reference = tfm::format("%s(%d): %s: Check failed.", rex::file_name(source_location.file_name()), source_location.line() - 2, source_location.function_name());

    EXPECT_EQ(message, reference);

    rex::set_trace_handler(old_trace_handler);
    rex::set_fail_handler(old_fail_handler);
}

TEST(debug, fail_fails)
{
    auto count = 0u;
    auto old_fail_handler = rex::set_fail_handler([&]()
    {
        count++;
    });

    rex::fail();

    EXPECT_EQ(count, 1u);

    rex::set_fail_handler(old_fail_handler);
}

TEST(debug, fail_traces)
{
    auto message = std::string{};
    auto old_trace_handler = rex::set_trace_handler([&](const std::string_view& m)
    {
        message = m;
    });
    auto old_fail_handler = rex::set_fail_handler([&]()
    {
        // do nothing
    });

    rex::fail();

    auto source_location = std::source_location::current();
    auto reference = tfm::format("%s(%d): %s: Unexpected code path.", rex::file_name(source_location.file_name()), source_location.line() - 2, source_location.function_name());

    EXPECT_EQ(message, reference);

    rex::set_trace_handler(old_trace_handler);
    rex::set_fail_handler(old_fail_handler);
}
