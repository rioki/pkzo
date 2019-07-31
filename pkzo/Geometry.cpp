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
    Geometry::Geometry(std::shared_ptr<Material> m)
    : material(m) {}

    Geometry::~Geometry() = default;

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = std::move(value);
    }

    std::shared_ptr<Material> Geometry::get_material()
    {
        return material;
    }
}
