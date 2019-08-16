// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "DynamicSphere.h"

namespace cubes
{
    DynamicSphere::DynamicSphere(float diameter, float mass, const std::shared_ptr<pkzo::Material>& material)
    : Body(mass)
    {
        // TODO
        auto geom = std::make_shared<pkzo::BoxGeometry>(glm::vec3(diameter, diameter, diameter), material);
        add_node(geom);

        auto collider = std::make_shared<pkzo::SphereCollider>(diameter);
        add_node(collider);
    }
}
