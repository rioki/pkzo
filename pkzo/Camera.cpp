// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace pkzo
{
    Camera::Camera() = default;
    Camera::~Camera() = default;

    void Camera::set_fov(float value)
    {
        fov = value;
    }

    float Camera::get_fov() const
    {
        return fov;
    }

    void Camera::set_resolution(glm::uvec2 value)
    {
        resolution = std::move(value);
    }

    glm::uvec2 Camera::get_resolution() const
    {
        return resolution;
    }

    glm::mat4 Camera::get_projection() const
    {
        // TODO get distance from scene
        auto distance = 1000.0f;
        auto aspect = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        auto fovy = glm::radians(fov) / aspect;
        return glm::perspective(fovy / 2.0f, fovy, 0.1f, distance);
    }

    glm::mat4 Camera::get_view() const
    {
        auto t = get_transform();
        auto eye = glm::vec3(t[3]);
        t[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        auto forward = glm::vec3(t * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
        auto up      = glm::vec3(t * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
        auto target = eye + forward;
        return glm::lookAt(eye, target, up);
    }
}
