// pkzo
// Copyright 2010-2024 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include <array>
#include <glm/glm.hpp>

#include "defines.h"

namespace pkzo
{
    constexpr size_t cpow(size_t base, size_t exp)
    {
        if (exp == 1)
        {
            return base;
        }
        else
        {
            return cpow(base, exp - 1) * base;
        }
    }

    template <glm::length_t Dim>
    class Bounds
    {
    public:
        constexpr Bounds() noexcept = default;
        constexpr Bounds(const glm::vec<Dim, float>& _min, const glm::vec<Dim, float>& _max)
        : min(_min), max(_max) {}

        constexpr const glm::vec<Dim, float>& get_min() const
        {
            return min;
        }

        constexpr const glm::vec<Dim, float>& get_max() const
        {
            return max;
        }

        constexpr glm::vec<Dim, float> get_size() const
        {
            return max - min;
        }

        constexpr glm::vec<Dim, float> get_center() const
        {
            return min + (get_size() * 0.5f);
        }

        constexpr std::array<glm::vec<Dim, float>, cpow(2, Dim)> get_points() const
        {
            // I have NO idea how to do this generically; we only use 2 and 3
            if constexpr (Dim == 2)
            {
                return std::array<glm::vec2, 4>{
                    glm::vec2{min.x, min.y},
                    glm::vec2{max.x, min.y},
                    glm::vec2{min.x, max.y},
                    glm::vec2{max.x, max.y},
                };
            }
            if constexpr (Dim == 3)
            {
                return std::array<glm::vec3, 8>{
                    glm::vec3{min.x, min.y, min.z},
                    glm::vec3{max.x, min.y, min.z},
                    glm::vec3{min.x, max.y, min.z},
                    glm::vec3{max.x, max.y, min.z},
                    glm::vec3{min.x, min.y, max.z},
                    glm::vec3{max.x, min.y, max.z},
                    glm::vec3{min.x, max.y, max.z},
                    glm::vec3{max.x, max.y, max.z},
                };
            }
        }

    private:
        glm::vec<Dim, float> min = glm::vec<Dim, float>(0.0f);
        glm::vec<Dim, float> max = glm::vec<Dim, float>(0.0f);
    };

    template <glm::length_t Dim> [[nodiscard]] constexpr
    Bounds<Dim> merge(const Bounds<Dim>& lhs, const Bounds<Dim>& rhs)
    {
        auto min = glm::min(lhs.get_min(), rhs.get_min());
        auto max = glm::max(lhs.get_max(), rhs.get_max());
        return Bounds<Dim>(min, max);
    }

    template <glm::length_t Dim> [[nodiscard]] constexpr
    Bounds<Dim> operator * (const glm::mat<Dim + 1, Dim + 1, float>& lhs, const Bounds<Dim>& rhs)
    {
        auto points = rhs.get_points();
        auto min = lhs * glm::vec<Dim + 1, float>(points[0], 1.0f);
        auto max = lhs * glm::vec<Dim + 1, float>(points[0], 1.0f);
        for (auto i = 1u; i < points.size(); i++)
        {
            min = glm::min(min, lhs * glm::vec<Dim + 1, float>(points[i], 1.0f));
            max = glm::max(max, lhs * glm::vec<Dim + 1, float>(points[i], 1.0f));
        }

        return Bounds<Dim>(glm::vec<Dim, float>(min), glm::vec<Dim, float>(max));
    }
}