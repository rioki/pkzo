// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "AmbientLight.h"

#include "RenderQueue.h"

namespace pkzo
{
    AmbientLight::AmbientLight(const glm::vec3& color)
    : Light(color) {}

    void AmbientLight::enqueue(RenderQueue& queue) const
    {
        queue.submit_ambient_light(color);
    }
}
