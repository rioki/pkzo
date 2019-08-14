// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "StaticBox.h"

namespace cubes
{
    StaticBox::StaticBox(const glm::vec3& size, const std::shared_ptr<pkzo::Material>& material)
    {
        auto geom = std::make_shared<pkzo::BoxGeometry>(size, material);
        add_node(geom);

        auto collider = std::make_shared<pkzo::BoxCollider>(size);
        add_node(collider);
    }
}
