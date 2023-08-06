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

#include <pkzo/debug.h>

#include "DebugMonitor.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(debug, trace)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    pkzo::trace("Ups! Did I do that?");
    pkzo::trace("Ok... So, what now?");

    std::this_thread::sleep_for(10ms);
    const auto ref = "test_debug.cpp(34): TestBody: Ups! Did I do that?\n"
                     "test_debug.cpp(35): TestBody: Ok... So, what now?\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}


TEST(debug, fail_dies)
{
    EXPECT_DEATH(pkzo::fail(), "");
}

TEST(debug, fail_traces)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    EXPECT_DEATH(pkzo::fail("Oh No!"), "");

    std::this_thread::sleep_for(10ms);
    const auto ref = "test_debug.cpp(53): TestBody: Oh No!\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}

TEST(debug, fail_traces_default)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    EXPECT_DEATH(pkzo::fail(), "");

    std::this_thread::sleep_for(10ms);
    const auto ref = "test_debug.cpp(64): TestBody: Unexpected failure.\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}

TEST(debug, check_true_passes)
{
    pkzo::check(true);
}

TEST(debug, check_false_dies)
{
    EXPECT_DEATH(pkzo::check(false), "");
}

TEST(debug, check_true_no_trace)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    pkzo::check(true, "Something Aweful!");

    std::this_thread::sleep_for(10ms);
    EXPECT_EQ("", debug_monitor.get_output());
}

TEST(debug, check_traces)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    EXPECT_DEATH(pkzo::check(false, "Something Aweful!"), "");

    std::this_thread::sleep_for(10ms);
    const auto ref = "test_debug.cpp(95): TestBody: Something Aweful!\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}


TEST(debug, check_traces_default)
{
    auto debug_monitor = pkzo::test::DebugMonitor{};

    EXPECT_DEATH(pkzo::check(false), "");

    std::this_thread::sleep_for(10ms);
    const auto ref = "test_debug.cpp(107): TestBody: Check failed.\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}
