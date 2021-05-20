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
#include "Camera.h"

namespace pkzo
{
    Camera::Camera(const glm::mat4& transform) noexcept
    : SceneNode(transform) {}

    void Camera::set_resolution(const glm::uvec2& value) noexcept
    {
        resolution = value;
    }

    const glm::uvec2& Camera::get_resolution() const noexcept
    {
        return resolution;
    }

    float Camera::get_aspect() const noexcept
    {
        return static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
    }

    glm::mat4 Camera::get_view() const noexcept
    {
        return glm::inverse(get_world_transform());
    }

    void Camera::look_at(const glm::vec3 pos, const glm::vec3 target, const glm::vec3 up)
    {
        set_transform(glm::inverse(glm::lookAt(pos, target, up)));
    }

}
