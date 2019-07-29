// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Camera.h"

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

    void Camera::setup(RenderQueue& queue) const
    {
        queue.set_perspective_camera(get_transform(), fov);
    }
}
