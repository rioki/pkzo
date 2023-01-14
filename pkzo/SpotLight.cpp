// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "SpotLight.h"

#include "Renderer.h"

namespace pkzo
{
    SpotLight::SpotLight(const glm::mat4& transform, const glm::vec3& _color, float _inner_angle, float _outer_angle) noexcept
    : Light(transform), color(_color), inner_angle(_inner_angle), outer_angle(_outer_angle) {}

    void SpotLight::set_color(const glm::vec3& value) noexcept
    {
        color = value;
        if (renderer)
        {
            renderer->update_light_color(render_handle, color);
        }
    }

    const glm::vec3& SpotLight::get_color() const noexcept
    {
        return color;
    }

    void SpotLight::set_inner_angle(float value) noexcept
    {
        inner_angle = value;
        if (renderer)
        {
            renderer->update_light_angles(render_handle, inner_angle, outer_angle);
        }
    }

    float SpotLight::get_inner_angle() const noexcept
    {
        return inner_angle;
    }

    void SpotLight::set_outer_angle(float value) noexcept
    {
        outer_angle = value;
        if (renderer)
        {
            renderer->update_light_angles(render_handle, inner_angle, outer_angle);
        }
    }

    float SpotLight::get_outer_angle() const noexcept
    {
        return outer_angle;
    }

    unsigned int SpotLight::register_light(Renderer& renderer) noexcept
    {
        return renderer.add_spot_light(get_world_transform(), color, inner_angle, outer_angle);
    }
}
