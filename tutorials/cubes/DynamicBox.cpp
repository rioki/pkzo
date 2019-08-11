// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "DynamicBox.h"

namespace cubes
{
    DynamicBox::DynamicBox(const glm::vec3& size, float mass, const std::shared_ptr<pkzo::Material>& material)
    : Body(mass)
    {
        auto geom = std::make_shared<pkzo::BoxGeometry>(size, material);
        add_node(geom);
    }
}
