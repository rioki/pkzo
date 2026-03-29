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

#include <array>
#include <glm/glm.hpp>

#include "api.h"

namespace pkzo
{
    template <glm::length_t D>
    class Bounds
    {
    public:
        using vec_t = glm::vec<D, float, glm::packed_highp>;

        Bounds()
        : min(0.0f), max(0.0f) {}

        Bounds(const vec_t& min, const vec_t& max)
        : min(min), max(max) {}

        const vec_t& get_min() const
        {
            return min;
        }

        const vec_t& get_max() const
        {
            return max;
        }

        vec_t get_size() const
        {
            return max - min;
        }

        vec_t get_center() const
        {
            return min + (get_size() * 0.5f);
        }

        vec_t get_extents() const
        {
            return get_size() * 0.5f;
        }

    private:
        vec_t min;
        vec_t max;
    };

    template <glm::length_t D>
    Bounds<D> merge(const Bounds<D>& lhs, const Bounds<D>& rhs)
    {
        auto min = glm::min(lhs.get_min(), rhs.get_min());
        auto max = glm::max(lhs.get_max(), rhs.get_max());
        return Bounds(min, max);
    }

    template <glm::length_t D, typename M = glm::mat<D + 1, D + 1, float, glm::packed_highp>>
    Bounds<D> transform(const M& m, const Bounds<D>& b)
    {
        using vec_t  = typename Bounds<D>::vec_t;
        using hvec_t = glm::vec<D + 1, float, glm::packed_highp>;
        using mat_t  = glm::mat<D, D, float, glm::packed_highp>;

        const auto center  = b.get_center();
        const auto extents = b.get_extents();

        const auto transformed_center_h = m * hvec_t(center, 1.0f);
        const vec_t transformed_center(transformed_center_h);

        mat_t linear(1.0f);
        for (glm::length_t c = 0; c < D; ++c)
        {
            for (glm::length_t r = 0; r < D; ++r)
            {
                linear[c][r] = m[c][r];
            }
        }

        mat_t abs_linear(1.0f);
        for (glm::length_t c = 0; c < D; ++c)
        {
            for (glm::length_t r = 0; r < D; ++r)
            {
                abs_linear[c][r] = glm::abs(linear[c][r]);
            }
        }

        const auto transformed_extents = abs_linear * extents;

        return Bounds<D>(
            transformed_center - transformed_extents,
            transformed_center + transformed_extents);
    }

    using Bounds2 = Bounds<2>;
    using Bounds3 = Bounds<3>;
}
