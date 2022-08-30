// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "texture_checks.h"

#include <ice/glm_io.h>

using namespace std::literals::string_literals;

namespace ice::test
{
    void save_test_output(const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value)
    {
        assert(lhs_value);
        assert(rhs_value);
        auto lhs_name  = get_test_output() / (get_test_name() + "-lhs.png"s);
        auto rhs_name  = get_test_output() / (get_test_name() + "-rhs.png"s);
        lhs_value->save(lhs_name);
        rhs_value->save(rhs_name);
    }


    void save_test_output_diff(const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value)
    {
        assert(lhs_value);
        assert(rhs_value);

        save_test_output(lhs_value, rhs_value);
        auto diff_name  = get_test_output() / (get_test_name() + "-diff.png"s);
        auto diff = ice::diff(lhs_value, rhs_value);
        diff->save(diff_name);
    }

    testing::AssertionResult compare_textures(const char* lhs_expression, const char* rhs_expression, const char* abs_error_expr, const std::shared_ptr<Texture>& lhs_value, const std::shared_ptr<Texture>& rhs_value, float abs_error)
    {
        if (lhs_value == nullptr)
        {
            return testing::AssertionFailure()
                << "The texture " << lhs_expression << " is null.";
        }

        if (rhs_value == nullptr)
        {
            return testing::AssertionFailure()
                << "The texture " << rhs_expression << " is null.";
        }

        if (lhs_value->get_size() != rhs_value->get_size())
        {
            save_test_output(lhs_value, rhs_value);

            return testing::AssertionFailure()
                << "The textures " << lhs_expression << " " << lhs_value->get_size()
                << " and " << rhs_expression << " " << rhs_value->get_size()
                << " have different size."
                << " Test output save to " << get_test_output() << ".";
        }

        auto diff_error = ice::compare(lhs_value, rhs_value);
        if (diff_error <= abs_error) {
            return testing::AssertionSuccess();
        }

        save_test_output_diff(lhs_value, rhs_value);
        return testing::AssertionFailure()
            << "The difference between " << lhs_expression << " and " << rhs_expression
            << " is " << diff_error  << ", which exceeds " << abs_error_expr << "."
            << " Test output save to " << get_test_output() << ".";
    }
}
