// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "PointLight.h"

#include "RenderQueue.h"

namespace pkzo
{
    PointLight::PointLight(const glm::vec3& color)
    : Light(color) {}

    void PointLight::enqueue(RenderQueue& queue) const
    {
        auto transform = get_transform();
        auto light_position = glm::vec3(transform[3]);

        queue.submit_point_light(color, light_position);
    }
}
