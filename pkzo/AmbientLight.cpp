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

#include "pch.h"

#include "AmbientLight.h"

namespace pkzo
{

    AmbientLight::AmbientLight(Init init)
    : Light({init.parent, init.transform}),
      color(init.color) {}

    AmbientLight::~AmbientLight() = default;

    void AmbientLight::set_color(const glm::vec3& value)
    {
        color = value;
    }

    LightType AmbientLight::get_type() const
    {
        return LightType::AMBIENT;
    }

    glm::vec3 AmbientLight::get_color() const
    {
        return color;
    }

    glm::vec3 AmbientLight::get_direction() const
    {
        return {};
    }

    glm::vec3 AmbientLight::get_position() const
    {
        return {};
    }

    glm::vec2 AmbientLight::get_angles() const
    {
        return {};
    }
}
