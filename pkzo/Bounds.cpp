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

#include "Bounds.h"

namespace pkzo
{
    Bounds::Bounds()
    : min(0.0f), max(0.0f) {}

    Bounds::Bounds(const glm::vec3& _min, const glm::vec3& _max)
    : min(_min), max(_max) {}

    const glm::vec3 Bounds::get_min() const
    {
        return min;
    }

    const glm::vec3 Bounds::get_max() const
    {
        return max;
    }

    glm::vec3 Bounds::get_size() const
    {
        return max - min;
    }

    glm::vec3 Bounds::get_center() const
    {
        return min + (get_size() * 0.5f);
    }

    std::array<glm::vec3, 8> Bounds::get_points() const
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

    Bounds merge(const Bounds& lhs, const Bounds& rhs)
    {
        auto min = glm::min(lhs.get_min(), rhs.get_min());
        auto max = glm::max(lhs.get_max(), rhs.get_max());
        return Bounds(min, max);
    }

    Bounds operator * (const glm::mat4& lhs, const Bounds& rhs)
    {
        auto points = rhs.get_points();
        auto min = lhs * glm::vec4(points[0], 1.0f);
        auto max = lhs * glm::vec4(points[0], 1.0f);
        for (auto i = 1u; i < points.size(); i++)
        {
            min = glm::min(min, lhs * glm::vec4(points[i], 1.0f));
            max = glm::max(max, lhs * glm::vec4(points[i], 1.0f));
        }

        return Bounds(glm::vec3(min), glm::vec3(max));
    }
}
