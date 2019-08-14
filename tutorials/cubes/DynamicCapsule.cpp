// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "DynamicCapsule.h"

namespace cubes
{
    DynamicCapsule::DynamicCapsule(float diameter, float height, float mass, const std::shared_ptr<pkzo::Material>& material)
    : Body(mass)
    {
        // TODO
        auto geom = std::make_shared<pkzo::BoxGeometry>(glm::vec3(diameter, diameter, height), material);
        add_node(geom);

        auto collider = std::make_shared<pkzo::CapsuleCollider>(diameter, height);
        add_node(collider);
    }
}
