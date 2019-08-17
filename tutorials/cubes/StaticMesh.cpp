// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "StaticMesh.h"

namespace cubes
{
    StaticMesh::StaticMesh(const std::shared_ptr<pkzo::Mesh> mesh, const std::shared_ptr<pkzo::Material>& material)
    {
        auto geom = std::make_shared<pkzo::MeshGeometry>(mesh, material);
        add_node(geom);

        auto collider = std::make_shared<pkzo::MeshCollider>(mesh);
        add_node(collider);
    }
}
