// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "test_env.h"

namespace ice::test
{
    std::filesystem::path get_asset_folder() noexcept
    {
        return std::filesystem::path(SOLUTION_DIR) / "assets";
    }

    std::filesystem::path get_test_input() noexcept
    {
        return std::filesystem::path(PROJECT_DIR) / "input";
    }

    std::filesystem::path get_test_output() noexcept
    {
        return std::filesystem::path(PROJECT_DIR) / "output";
    }

    std::string get_test_name() noexcept
    {
        auto test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        return std::string(test_info->test_suite_name()) + "-" + std::string(test_info->name());
    }
}