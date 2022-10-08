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
#include "Camera.h"

#include "Renderer.h"

namespace ice
{
    Camera::Camera() noexcept
    : Camera(glm::mat4(1.0f), 90.0f, glm::uvec2(1600, 900)) {}

    Camera::Camera(const glm::mat4& _transform, const float _fov, const glm::uvec2 _resolution) noexcept
    : SceneNode(_transform), fov(_fov), resolution(_resolution)
    {
        on_move([this] ()
        {
            if (renderer)
            {
                renderer->upate_camera_view(render_handle, get_world_transform());
            }
        });
    }

    float Camera::get_fov() const noexcept
    {
        return fov;
    }

    void Camera::set_fov(const float value) noexcept
    {
        fov = value;
        if (renderer)
        {
            renderer->upate_camera_projection(render_handle, resolution, fov);
        }
    }

    glm::uvec2 Camera::get_resolution() const noexcept
    {
        return resolution;
    }

    void Camera::set_resolution(const glm::uvec2 value) noexcept
    {
        resolution = value;
        if (renderer)
        {
            renderer->upate_camera_projection(render_handle, resolution, fov);
        }
    }

    void Camera::activate()
    {
        assert(renderer == nullptr);

        auto scene = get_root();
        assert(scene != nullptr);
        if (renderer = scene->get_renderer())
        {
            render_handle = renderer->add_camera(get_world_transform(), resolution, fov);
        }
    }

    void Camera::deactivate()
    {
        if (renderer != nullptr)
        {
            renderer->remove_camera(render_handle);
            render_handle = 0;
            renderer      = nullptr;
        }
    }
}