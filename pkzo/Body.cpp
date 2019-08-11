// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Body.h"

#include "Engine.h"
#include "PhysicSystem.h"

namespace pkzo
{
    Body::Body(float m)
    : mass(m) {}

    void Body::set_mass(float value)
    {
        mass = value;
    }

    float Body::get_mass() const
    {
        return mass;
    }

    void Body::activate()
    {
        SceneNodeGroup::activate();

        auto& engine = get_engine();
        auto physic_system = engine.get_system<PhysicSystem>();
        if (physic_system)
        {
            physic_system->add(this);
        }
    }

    void Body::deactivate()
    {
        auto& engine = get_engine();
        auto physic_system = engine.get_system<PhysicSystem>();
        if (physic_system)
        {
            physic_system->remove(this);
        }
        SceneNodeGroup::deactivate();
    }
}
