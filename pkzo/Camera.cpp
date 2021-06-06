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
#include "HitArea.h"
#include "Scene.h"

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

    std::optional<TestResult> Camera::pick(const glm::vec2 pos) const noexcept
    {
        auto screen = get_scene();
        DBG_ASSERT(screen);

        auto proj = get_projection();
        auto view = get_view();

        auto near_vec = glm::unProject(glm::vec3(pos, -1.0f), view, proj, glm::vec4(0.0f, 0.0f, resolution.x, resolution.y));
        auto far_vec  = glm::unProject(glm::vec3(pos, 1.0f), view, proj, glm::vec4(0.0f, 0.0f, resolution.x, resolution.y));

        return screen->test_ray(near_vec, far_vec, physics::CollisionGroup::INTERACTION, physics::CollisionGroup::ALL);
    }

    void Camera::handle_mouse_move(const glm::vec2 pos, const glm::vec2 mov) const noexcept
    {
        auto result = pick(pos);
        if (result)
        {
            auto hit_area = std::dynamic_pointer_cast<HitArea>(result.value().node);
            if (hit_area)
            {
                auto dir = glm::vec3(mov, 1.0f); // TODO
                hit_area->handle_mouse_move(result.value().position, dir);
            }
        }

    }

    void Camera::handle_mouse_down(const glm::vec2 pos, MouseButton button) const noexcept
    {
        auto result = pick(pos);
        if (result)
        {
            auto hit_area = std::dynamic_pointer_cast<HitArea>(result.value().node);
            if (hit_area)
            {
                hit_area->handle_mouse_down(result.value().position, button);
                mouse_down_hit = hit_area;
            }
        }
    }

    void Camera::handle_mouse_up(const glm::vec2 pos, MouseButton button) const noexcept
    {
        auto result = pick(pos);
        if (result)
        {
            auto hit_area = std::dynamic_pointer_cast<HitArea>(result.value().node);
            if (hit_area)
            {
                hit_area->handle_mouse_up(result.value().position, button);
            }
            if (hit_area != mouse_down_hit)
            {
                hit_area->handle_mouse_up_outside(result.value().position, button);
            }
        }
    }
}
