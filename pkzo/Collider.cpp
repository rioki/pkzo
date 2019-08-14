// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Collider.h"

#include "Engine.h"
#include "PhysicSystem.h"

namespace pkzo
{
    void Collider::activate()
    {
        SceneNode::activate();

        auto& engine = get_engine();
        auto physics = engine.get_system<PhysicSystem>();
        if (physics)
        {
            physics->add(this);
        }
    }

    void Collider::deactivate()
    {
        auto& engine = get_engine();
        auto physics = engine.get_system<PhysicSystem>();
        if (physics)
        {
            physics->remove(this);
        }

        SceneNode::deactivate();
    }
}
