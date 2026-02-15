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
    class PKZO_EXPORT Bounds
    {
    public:
        Bounds();
        Bounds(const glm::vec3& min, const glm::vec3& max);

        const glm::vec3 get_min() const;
        const glm::vec3 get_max() const;

        glm::vec3 get_size() const;
        glm::vec3 get_center() const;

        std::array<glm::vec3, 8> get_points() const;

    private:
        glm::vec3 min;
        glm::vec3 max;
    };

    PKZO_EXPORT Bounds merge(const Bounds& lhs, const Bounds& rhs);

    PKZO_EXPORT Bounds operator * (const glm::mat4& lhs, const Bounds& rhs);
}
