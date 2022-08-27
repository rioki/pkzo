// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once

#include <string>
#include <filesystem>

namespace ice::test
{
    std::filesystem::path get_test_input() noexcept;
    std::filesystem::path get_test_output() noexcept;
    std::string get_test_name() noexcept;
}