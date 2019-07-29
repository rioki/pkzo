// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "DirectionalLight.h"

#include "RenderQueue.h"

namespace pkzo
{
    DirectionalLight::DirectionalLight(const glm::vec3& color)
    : Light(color) {}

    void DirectionalLight::enqueue(RenderQueue& queue) const
    {
        auto rotation = glm::mat3(get_transform());
        auto light_direction = rotation * glm::vec3{0.0f, 0.0f, -1.0f};

        queue.submit_directional_light(color, light_direction);
    }
}
