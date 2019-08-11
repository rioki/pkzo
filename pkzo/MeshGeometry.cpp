// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "MeshGeometry.h"

#include "dbg.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderQueue.h"

namespace pkzo
{
    MeshGeometry::MeshGeometry(std::shared_ptr<Mesh> me, const std::shared_ptr<Material>& ma)
    : Geometry(ma), mesh(std::move(me)) {}

    MeshGeometry::~MeshGeometry() = default;

    void MeshGeometry::set_mesh(std::shared_ptr<Mesh> value)
    {
        mesh = std::move(value);
    }

    std::shared_ptr<Mesh> MeshGeometry::get_mesh() const
    {
        return mesh;
    }

    void MeshGeometry::enqueue(RenderQueue& queue) const
    {
        queue.submit_mesh(get_world_transform(), mesh, material);
    }
}