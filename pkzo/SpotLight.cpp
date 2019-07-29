// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SpotLight.h"

#include "RenderQueue.h"

namespace pkzo
{
    void SpotLight::set_angle(float value)
    {
        angle = value;
    }

    float SpotLight::get_angle() const
    {
        return angle;
    }

    void SpotLight::enqueue(RenderQueue& queue) const
    {
        auto transform = get_transform();
        auto rotation = glm::mat3(transform);
        auto light_position = glm::vec3(transform[3]);
        auto light_direction = rotation * glm::vec3{0.0f, 0.0f, -1.0f};

        queue.submit_spot_light(color, light_position, light_direction, angle);
    }
}
