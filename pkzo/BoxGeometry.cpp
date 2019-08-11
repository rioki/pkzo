// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "BoxGeometry.h"

#include "dbg.h"
#include "Engine.h"
#include "RenderQueue.h"
#include "PhysicSystem.h"

namespace pkzo
{
    BoxGeometry::BoxGeometry(const glm::vec3& s, const std::shared_ptr<Material>& material)
    : Geometry(material), size(s) {}

    BoxGeometry::~BoxGeometry() = default;

    void BoxGeometry::set_size(const glm::vec3& value)
    {
        size = value;
    }

    const glm::vec3& BoxGeometry::get_size() const
    {
        return size;
    }

    void BoxGeometry::enqueue(RenderQueue& queue) const
    {
        queue.submit_box(get_world_transform(), size, material);
    }

    void BoxGeometry::activate()
    {
        Geometry::activate();

        auto& engine = get_engine();
        auto physics = engine.get_system<PhysicSystem>();
        if (physics)
        {
            physics->add(this);
        }
    }

    void BoxGeometry::deactivate()
    {
        auto& engine = get_engine();
        auto physics = engine.get_system<PhysicSystem>();
        if (physics)
        {
            physics->remove(this);
        }

        Geometry::deactivate();
    }

    void BoxGeometry::update(float dt)
    {
        //
    }
}
