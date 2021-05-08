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

#include "pch.h"
#include "SpotLight.h"

#include "Parameters.h"

namespace pkzo
{
    SpotLight::SpotLight(const glm::mat4& transform, const glm::vec3& c, float ia, float oa) noexcept
    : Light(transform), color(c), inner_angle(ia), outer_angle(oa) {}

    void SpotLight::set_color(const glm::vec3& value) noexcept
    {
        color = value;
    }

    const glm::vec3& SpotLight::get_color() const noexcept
    {
        return color;
    }

    void SpotLight::set_outer_angle(float value) noexcept
    {
        outer_angle = value;
    }

    float SpotLight::get_outer_angle() const noexcept
    {
        return outer_angle;
    }

    std::shared_ptr<Parameters> SpotLight::get_parameters() const noexcept
    {
        auto wt = get_world_transform();
        auto dir = wt * glm::vec4(0.0, 0.0, -1.0, 0.0);
        auto pos = wt[3];

        return make_shared_parameters({
            {"pkzo_LightType", static_cast<glm::uint>(LightType::SPOT)},
            {"pkzo_LightColor", color},
            {"pkzo_LightDirection", glm::vec3(dir)},
            {"pkzo_LightPosition", glm::vec3(pos)},
            {"pkzo_LightInnerAngle", glm::radians(inner_angle)},
            {"pkzo_LightOuterAngle", glm::radians(outer_angle)},
        });
    }
}