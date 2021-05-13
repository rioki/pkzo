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

#pragma once

#include <string>
#include <tuple>
#include <filesystem>
#include <gtest/gtest.h>
#include <pkzo/Texture.h>
#include <pkzo/glmio.h>

namespace pkzo::test
{
    constexpr auto ENGINE_ID = "pkzo-test";

    //! Get system temp folder.
    std::filesystem::path get_temp_folder();
    //! Get the system user folder.
    //!
    //! On Windows this is %LOCALAPPDATA%
    std::filesystem::path get_user_folder();

    std::filesystem::path get_test_temp() noexcept;
    std::filesystem::path get_test_ref() noexcept;
    std::string get_test_name() noexcept;
    void save_test_output(const Texture& lhs_value, const Texture& rhs_value);
    void save_test_output_diff(const Texture& lhs_value, const Texture& rhs_value);

    testing::AssertionResult compare_textures(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const Texture& lhs_value, const Texture& rhs_value, float abs_error);

    //! Make sure the settings the test engine loads are deterministic
    void setup_test_settings(const glm::uvec2 resolution = glm::uvec2(800u, 600u));
}

#define EXPECT_TEXTURE_NEAR(val1, val2, abs_error) EXPECT_PRED_FORMAT3(::pkzo::test::compare_textures, val1, val2, abs_error)
#define ASSERT_TEXTURE_NEAR(val1, val2, abs_error) ASSERT_PRED_FORMAT3(::pkzo::test::compare_textures, val1, val2, abs_error)
#define EXPECT_TEXTURE_EQ(val1, val2) EXPECT_TEXTURE_NEAR(val1, val2, 0.0f)
#define ASSERT_TEXTURE_EQ(val1, val2) ASSERT_TEXTURE_NEAR(val1, val2, 0.0f)

#define _TEXTURE_REF_ pkzo::Texture(get_test_ref() / (get_test_name() + "-ref.png"))
#define EXPECT_TEXTURE_REF_NEAR(val) EXPECT_TEXTURE_NEAR(_TEXTURE_REF_, val2, 0.0f)
#define ASSERT_TEXTURE_REF_NEAR(val) EXPECT_TEXTURE_NEAR(_TEXTURE_REF_, val2, 0.0f)
#define EXPECT_TEXTURE_REF_EQ(val) EXPECT_TEXTURE_EQ(_TEXTURE_REF_, val)
#define ASSERT_TEXTURE_REF_EQ(val) EXPECT_TEXTURE_EQ(_TEXTURE_REF_, val)
