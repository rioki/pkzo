// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Geometry.h"

#include "dbg.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderQueue.h"

namespace pkzo
{
    Geometry::Geometry() = default;
    Geometry::~Geometry() = default;

    void Geometry::set_mesh(std::shared_ptr<Mesh> value)
    {
        mesh = std::move(value);
    }

    std::shared_ptr<Mesh> Geometry::get_mesh() const
    {
        return mesh;
    }

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = std::move(value);
    }

    std::shared_ptr<Material> Geometry::get_material()
    {
        return material;
    }

    void Geometry::enqueue(RenderQueue& queue) const
    {
        PKZO_ASSERT(material);
        PKZO_ASSERT(mesh);

        queue.submit_mesh(get_transform(), mesh, material);
    }
}
