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
#include "DirectionalLight.h"

#include "Parameters.h"

namespace pkzo
{
    DirectionalLight::DirectionalLight(const glm::mat4& transform, const glm::vec3& c) noexcept
    : Light(transform), color(c) {}

    void DirectionalLight::set_color(const glm::vec3& value) noexcept
    {
        color = value;
    }

    const glm::vec3& DirectionalLight::get_color() const noexcept
    {
        return color;
    }

    std::shared_ptr<Parameters> DirectionalLight::get_parameters() const noexcept
    {
        auto wt = get_world_transform();
        auto dir = wt * glm::vec4(0.0, 0.0, -1.0, 0.0);

        return make_shared_parameters({
            {"pkzo_LightType", static_cast<glm::uint>(LightType::DIRECTIONAL)},
            {"pkzo_LightColor", color},
            {"pkzo_LightDirection", glm::vec3(dir)},
        });
    }
}