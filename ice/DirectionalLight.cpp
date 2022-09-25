// Ice Engine
// Copyright 2022 Sean Farrell
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
#include "DirectionalLight.h"

#include "SceneRenderer.h"

namespace ice
{
    DirectionalLight::DirectionalLight(const glm::mat4& _transform, const glm::vec3& _color) noexcept
    : Light(_transform), color(_color) {}

    void DirectionalLight::set_color(const glm::vec3& value) noexcept
    {
        color = value;
        if (renderer)
        {
            renderer->update_light_color(render_handle, color);
        }
    }

    const glm::vec3& DirectionalLight::get_color() const noexcept
    {
        return color;
    }

    unsigned int DirectionalLight::register_light(SceneRenderer& renderer) noexcept
    {
        return renderer.add_directional_light(get_world_transform(), color);
    }
}