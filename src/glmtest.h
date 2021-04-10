// glm gtest comparators
// Copyright © 2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <gtest/gtest.h>

#include "glmio.h"

namespace internal
{
    template <typename RawType>
    testing::AssertionResult CmpHelperGlmNear(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const RawType& lhs_value, const RawType& rhs_value, typename RawType::value_type abs_error)
    {
        if (glm::all(glm::epsilonEqual(lhs_value, rhs_value, abs_error))) {
            return testing::AssertionSuccess();
        }
        auto diff = glm::abs(lhs_value - rhs_value);
        return testing::AssertionFailure()
            << "The difference between " << lhs_expression << " and " << rhs_expression
            << " is " << diff  << ", which exceeds " << abs_error_expr << ", where\n"
            << lhs_expression << " evaluates to " << lhs_value << ",\n"
            << rhs_expression << " evaluates to " << rhs_value << ", and\n"
            << abs_error_expr << " evaluates to " << abs_error << ".";
    }

    template <typename RawType>
    testing::AssertionResult CmpHelperGlmEQ(const char* lhs_expression, const char* rhs_expression, const RawType& lhs_value, const RawType& rhs_value)
    {
        if (glm::all(glm::equal(lhs_value, rhs_value))) {
            return testing::AssertionSuccess();
        }

        ::std::stringstream lhs_ss;
        lhs_ss << lhs_value;

        ::std::stringstream rhs_ss;
        rhs_ss << rhs_value;
        return testing::internal::EqFailure(lhs_expression,
                         rhs_expression,
                         testing::internal::StringStreamToString(&lhs_ss),
                         testing::internal::StringStreamToString(&rhs_ss),
                         false);
    }
}

#define EXPECT_GLM_NEAR(val1, val2, abs_error) EXPECT_PRED_FORMAT3(::internal::CmpHelperGlmNear, val1, val2, abs_error)
#define ASSERT_GLM_NEAR(val1, val2, abs_error) ASSERT_PRED_FORMAT3(::internal::CmpHelperGlmNear, val1, val2, abs_error)
#define EXPECT_GLM_EQ(val1, val2) EXPECT_PRED_FORMAT2(::internal::CmpHelperGlmEQ, val1, val2)
#define ASSERT_GLM_EQ(val1, val2) ASSERT_PRED_FORMAT2(::internal::CmpHelperGlmEQ, val1, val2)
