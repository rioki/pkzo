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