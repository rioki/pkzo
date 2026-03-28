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

#include "Camera.h"

#include "Scene.h"
#include "SceneRenderer.h"

namespace pkzo3d
{
    Camera::Camera(Specs specs)
    : Node({specs.parent, specs.transform})
    {
        auto renderer = get_scene()->get_renderer();
        renderer->add(this);

        on_move([this] () {
            view_matrix_cache = std::nullopt;
        });
    }

    Camera::~Camera()
    {
        auto renderer = get_scene()->get_renderer();
        renderer->remove(this);
    }

    void Camera::set_fov(float value)
    {
        fov = value;
        projection_matrix_cache = std::nullopt;
    }

    float Camera::get_fov() const
    {
        return fov;
    }

    void Camera::set_distance(float value)
    {
        distance = value;
        projection_matrix_cache = std::nullopt;
    }

    float Camera::get_distance() const
    {
        return distance;
    }

    void Camera::set_resolution(glm::uvec2 value)
    {
        resolution = value;
        projection_matrix_cache = std::nullopt;
    }

    glm::uvec2 Camera::get_resolution() const
    {
        return resolution;
    }

    glm::mat4 Camera::get_projection_matrix() const
    {
        if (projection_matrix_cache)
        {
            return *projection_matrix_cache;
        }

        auto aspect            = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        auto fovy              = 2.0f * std::atan(std::tan(glm::radians(fov) / 2.0f) / aspect);
        auto projection_matrix = glm::perspective(fovy, aspect, 0.01f, distance);

        projection_matrix_cache = projection_matrix;
        return projection_matrix;
    }

    glm::mat4 Camera::get_view_matrix() const
    {
        if (view_matrix_cache)
        {
            return *view_matrix_cache;
        }

        auto view_matrix = glm::inverse(get_global_transform());

        view_matrix_cache = view_matrix;
        return view_matrix;
    }
}
