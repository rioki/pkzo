// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once

#include <gtest/gtest.h>
#include <ice/Texture.h>

#include "test_utils.h"

namespace ice::test
{
    void save_test_output(const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value);
    void save_test_output_diff(const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value);

    testing::AssertionResult compare_textures(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value, float abs_error);
}

#define EXPECT_TEXTURE_NEAR(val1, val2, abs_error) EXPECT_PRED_FORMAT3(::ice::test::compare_textures, val1, val2, abs_error)
#define ASSERT_TEXTURE_NEAR(val1, val2, abs_error) ASSERT_PRED_FORMAT3(::ice::test::compare_textures, val1, val2, abs_error)
#define EXPECT_TEXTURE_EQ(val1, val2) EXPECT_TEXTURE_NEAR(val1, val2, 0.0f)
#define ASSERT_TEXTURE_EQ(val1, val2) ASSERT_TEXTURE_NEAR(val1, val2, 0.0f)

#define _TEXTURE_REF_ std::make_shared<ice::Texture>(::ice::test::get_test_input() / (::ice::test::get_test_name() + "-ref.png"))
#define EXPECT_TEXTURE_REF_NEAR(val) EXPECT_TEXTURE_NEAR(_TEXTURE_REF_, val2, 0.0f)
#define ASSERT_TEXTURE_REF_NEAR(val) EXPECT_TEXTURE_NEAR(_TEXTURE_REF_, val2, 0.0f)
#define EXPECT_TEXTURE_REF_EQ(val) EXPECT_TEXTURE_EQ(_TEXTURE_REF_, val)
#define ASSERT_TEXTURE_REF_EQ(val) EXPECT_TEXTURE_EQ(_TEXTURE_REF_, val)
