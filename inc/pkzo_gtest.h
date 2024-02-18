// Neon Skirmish
// Copyright 2023 Sean Farrell
// All rights reserved.

#pragma once

#include <filesystem>

#include <gtest/gtest.h>

#include <glm_io.h>
#include <pkzo/Image.h>

#include <test_env.h>

namespace pkzo::test
{
    using namespace std::string_literals;
    using namespace testing;

    inline
    void save_test_output(const Image& lhs_value, const Image& rhs_value)
    {

        auto lhs_name  = get_test_output() / (get_test_name() + "-lhs.png"s);
        auto rhs_name  = get_test_output() / (get_test_name() + "-rhs.png"s);
        lhs_value.save(lhs_name);
        rhs_value.save(rhs_name);
    }


    inline
    void save_test_output_diff(const Image& lhs_value, const Image& rhs_value)
    {
        save_test_output(lhs_value, rhs_value);
        auto diff_name  = get_test_output() / (get_test_name() + "-diff.png"s);
        diff(lhs_value, rhs_value).save(diff_name);
    }

    inline
    AssertionResult compare_images(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const Image& lhs_value, const Image& rhs_value, float abs_error)
    {
        if (lhs_value.get_size() != rhs_value.get_size())
        {
            save_test_output(lhs_value, rhs_value);

            return AssertionFailure()
                << "The images " << lhs_expression << " " << lhs_value.get_size()
                << " and " << rhs_expression << " " << rhs_value.get_size()
                << " have different size."
                << " Test output save to " << get_test_output() << ".";
        }

        auto diff_error = compare(lhs_value, rhs_value);
        if (diff_error <= abs_error) {
            return AssertionSuccess();
        }

        save_test_output_diff(lhs_value, rhs_value);
        return AssertionFailure()
            << "The difference between " << lhs_expression << " and " << rhs_expression
            << " is " << diff_error  << ", which exceeds " << abs_error_expr << "."
            << " Test output save to " << get_test_output() << ".";
    }

    inline
    AssertionResult compare_images_reference(const char* expression, const char* abs_error_expr, const Image& value, float abs_error)
    {
        auto ref_name = get_test_name() + "-ref.png"s;
        auto ref_file = get_test_input() / "references" / ref_name;

        if (!std::filesystem::exists(ref_file))
        {
            auto rhs_name  = get_test_output() / (get_test_name() + "-rhs.png"s);
            value.save(rhs_name);
            return AssertionFailure()
                << "The reference image " << ref_name << " does not exist."
                << " Test input directory is " << get_test_input() << "."
                << " Test output save to " << get_test_output() << ".";
        }

        auto ref_value = Image(ref_file);

        return compare_images(ref_name.data(), expression, abs_error_expr, ref_value, value, abs_error);
    }
}

#define EXPECT_IMAGE_NEAR(val1, val2, abs_error) EXPECT_PRED_FORMAT3(::pkzo::test::compare_images, val1, val2, abs_error)
#define ASSERT_IMAGE_NEAR(val1, val2, abs_error) ASSERT_PRED_FORMAT3(::pkzo::test::compare_images, val1, val2, abs_error)
#define EXPECT_IMAGE_EQ(val1, val2) EXPECT_IMAGE_NEAR(val1, val2, 0.0f)
#define ASSERT_IMAGE_EQ(val1, val2) ASSERT_IMAGE_NEAR(val1, val2, 0.0f)

#define EXPECT_IMAGE_REF_NEAR(val, abs_error) EXPECT_PRED_FORMAT2(::pkzo::test::compare_images_reference, val, abs_error)
#define ASSERT_IMAGE_REF_NEAR(val, abs_error) ASSERT_PRED_FORMAT2(::pkzo::test::compare_images_reference, val, abs_error)
#define EXPECT_IMAGE_REF_EQ(val) EXPECT_IMAGE_REF_NEAR(val, 0.0f)
#define ASSERT_IMAGE_REF_EQ(val) ASSERT_IMAGE_REF_NEAR(val, 0.0f)
