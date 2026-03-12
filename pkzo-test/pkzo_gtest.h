// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#pragma once

#include <filesystem>

#include <gtest/gtest.h>

#include <pkzo/pkzo.h>
#include <glm/gtx/io.hpp>

namespace pkzo::test
{
    using namespace testing;

    inline
    std::filesystem::path get_test_input()
    {
        return std::filesystem::path(PROJECT_DIR) / "input";
    }

    inline
    std::filesystem::path get_test_references() noexcept
    {
        return get_test_input() / "references";
    }

    inline
    std::filesystem::path get_test_output() noexcept
    {
       return std::filesystem::path(SOLUTION_DIR) / ".int/test";
    }

    inline
    std::string get_test_name() noexcept
    {
        auto test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        return std::string(test_info->test_suite_name()) + "-" + std::string(test_info->name());
    }

    inline
    void save_test_output(const std::shared_ptr<MemoryTexture>& lhs_value, const std::shared_ptr<MemoryTexture>& rhs_value)
    {
        assert(lhs_value != nullptr);
        lhs_value->save(get_test_output() / (get_test_name() + "-lhs.png"));

        assert(rhs_value != nullptr);
        rhs_value->save(get_test_output() / (get_test_name() + "-rhs.png"));
    }


    inline
    void save_test_output_diff(const std::shared_ptr<MemoryTexture>& lhs_value, const std::shared_ptr<MemoryTexture>& rhs_value)
    {
        assert(lhs_value != nullptr);
        assert(rhs_value != nullptr);

        save_test_output(lhs_value, rhs_value);
        auto diff_name  = get_test_output() / (get_test_name() + "-diff.png");
        diff(lhs_value, rhs_value)->save(diff_name);
    }

    inline
    AssertionResult compare_images(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value, float abs_error)
    {
        if (lhs_value == rhs_value)
        {
            return AssertionSuccess();
        }

        if (lhs_value == nullptr)
        {
            return AssertionFailure() << "The texture " << lhs_expression << " is null.";
        }

        if (rhs_value == nullptr)
        {
            return AssertionFailure() << "The texture " << rhs_expression << " is null.";
        }

        auto lhs_mem = lhs_value->download();
        auto rhs_mem = rhs_value->download();

        if (lhs_value->get_size() != rhs_value->get_size())
        {
            save_test_output(lhs_mem, rhs_mem);

            return AssertionFailure()
                << "The texture " << lhs_expression << " " << lhs_value->get_size()
                << " and " << rhs_expression << " " << rhs_value->get_size()
                << " have different size."
                << " Test output save to " << get_test_output() << ".";
        }

        auto diff_error = compare(lhs_mem, rhs_mem);
        if (diff_error <= abs_error)
        {
            return AssertionSuccess();
        }

        save_test_output_diff(lhs_mem, rhs_mem);
        return AssertionFailure()
            << "The difference between " << lhs_expression << " and " << rhs_expression
            << " is " << diff_error  << ", which exceeds " << abs_error_expr << "."
            << " Test output save to " << get_test_output() << ".";
    }

    inline
    AssertionResult compare_texture_reference(const char* expression, const char* abs_error_expr, const std::shared_ptr<Texture>& value, float abs_error)
    {
        auto ref_name = get_test_name() + "-ref.png";
        auto ref_file = get_test_references() / ref_name;

        if (!std::filesystem::exists(ref_file))
        {
            auto rhs_name  = get_test_output() / (get_test_name() + "-rhs.png");
            auto mem = value->download();
            mem->save(rhs_name);
            return AssertionFailure()
                << "The reference image " << ref_file << " does not exist."
                << " Test input directory is " << get_test_input() << "."
                << " Test output save to " << get_test_output() << ".";
        }

        auto ref_value = Texture::load_file({ .file = ref_file });

        return compare_images(ref_name.data(), expression, abs_error_expr, ref_value, value, abs_error);
    }
}

#define EXPECT_TEXTURE_NEAR(val1, val2, abs_error) EXPECT_PRED_FORMAT3(::pkzo::test::compare_texture, val1, val2, abs_error)
#define ASSERT_TEXTURE_NEAR(val1, val2, abs_error) ASSERT_PRED_FORMAT3(::pkzo::test::compare_texture, val1, val2, abs_error)
#define EXPECT_TEXTURE_EQ(val1, val2) EXPECT_TEXTURE_NEAR(val1, val2, 0.0f)
#define ASSERT_TEXTURE_EQ(val1, val2) ASSERT_TEXTURE_NEAR(val1, val2, 0.0f)

#define EXPECT_TEXTURE_REF_NEAR(val, abs_error) EXPECT_PRED_FORMAT2(::pkzo::test::compare_texture_reference, val, abs_error)
#define ASSERT_TEXTURE_REF_NEAR(val, abs_error) ASSERT_PRED_FORMAT2(::pkzo::test::compare_texture_reference, val, abs_error)
#define EXPECT_TEXTURE_REF_EQ(val) EXPECT_TEXTURE_REF_NEAR(val, 0.0f)
#define ASSERT_TEXTURE_REF_EQ(val) ASSERT_TEXTURE_REF_NEAR(val, 0.0f)
