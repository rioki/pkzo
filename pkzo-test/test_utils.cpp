//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "test_utils.h"

#include <pkzo/Settings.h>

namespace pkzo::test
{
    using namespace std::literals::string_literals;


    std::filesystem::path get_test_temp() noexcept
    {
        return std::filesystem::path("../../data/temp/");
    }

    std::filesystem::path get_test_ref() noexcept
    {
        return std::filesystem::path("../../data/references/");
    }

    std::string get_test_name() noexcept
    {
        auto test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        return std::string(test_info->test_suite_name()) + "-"s + std::string(test_info->name());
    }

    void save_test_output(const Texture& lhs_value, const Texture& rhs_value)
    {

        auto lhs_name  = get_test_temp() / (get_test_name() + "-lhs.png"s);
        auto rhs_name  = get_test_temp() / (get_test_name() + "-rhs.png"s);
        lhs_value.save(lhs_name);
        rhs_value.save(rhs_name);
    }


    void save_test_output_diff(const Texture& lhs_value, const Texture& rhs_value)
    {
        save_test_output(lhs_value, rhs_value);
        auto diff_name  = get_test_temp() / (get_test_name() + "-diff.png"s);
        pkzo::diff(lhs_value, rhs_value).save(diff_name);
    }

    testing::AssertionResult compare_textures(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const Texture& lhs_value, const Texture& rhs_value, float abs_error)
    {
        if (lhs_value.get_size() != rhs_value.get_size())
        {
            save_test_output(lhs_value, rhs_value);

            return testing::AssertionFailure()
                << "The textures " << lhs_expression << " " << lhs_value.get_size()
                << " and " << rhs_expression << " " << rhs_value.get_size()
                << " have different size."
                << " Test output save to " << get_test_temp() << ".";
        }

        auto diff_error = pkzo::compare(lhs_value, rhs_value);
        if (diff_error <= abs_error) {
            return testing::AssertionSuccess();
        }

        save_test_output_diff(lhs_value, rhs_value);
        return testing::AssertionFailure()
            << "The difference between " << lhs_expression << " and " << rhs_expression
            << " is " << diff_error  << ", which exceeds " << abs_error_expr << "."
            << " Test output save to " << get_test_temp() << ".";
    }
}
