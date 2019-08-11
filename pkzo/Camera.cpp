// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderQueue.h"

namespace pkzo
{
    void Camera::set_fov(float value)
    {
        fov = value;
    }

    float Camera::get_fov() const
    {
        return fov;
    }

    glm::mat4 Camera::get_projection_matrix(float aspect, float distance) const
    {
        auto fovy = glm::radians(fov / 2.0f) * aspect;
        return glm::perspective(fovy / 2.0f, fovy, 0.1f, distance);
    }

    glm::mat4 Camera::get_view_matrix() const
    {
        auto transform = get_world_transform();
        auto eye      = glm::vec3(transform[3]);
        auto rotation = glm::mat3(transform);
        auto forward  = glm::vec3(rotation * glm::vec3(0.0f, 0.0f, -1.0f));
        auto up       = glm::vec3(rotation * glm::vec3(0.0f, 1.0f, 0.0f));
        auto target   = eye + forward;
        return glm::lookAt(eye, target, up);
    }

    void Camera::setup(RenderQueue& queue) const
    {
        queue.set_perspective_camera(get_world_transform(), fov);
    }
}
