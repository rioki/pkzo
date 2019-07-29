// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Light.h"

namespace pkzo
{
    Light::Light(const glm::vec3& c)
    : color(c) {}

    void Light::set_color(const glm::vec3& value)
    {
        color = value;
    }

    const glm::vec3& Light::get_color() const
    {
        return color;
    }
}
