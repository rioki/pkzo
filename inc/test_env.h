// Ice Engine
// Copyright 2023 Sean Farrell
// All rights reserved.

#pragma once

#include <gtest/gtest.h>

#include <filesystem>

namespace testing
{
    using namespace std::string_literals;

    inline
    std::filesystem::path get_test_input() noexcept
    {
        return std::filesystem::path(PROJECT_DIR) / "input"s;
    }

    inline
    std::filesystem::path get_test_output() noexcept
    {
       return std::filesystem::path(PROJECT_DIR) / "output"s;
    }

    inline
    std::string get_test_name() noexcept
    {
        auto test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        return std::string(test_info->test_suite_name()) + "-"s + std::string(test_info->name());
    }
}