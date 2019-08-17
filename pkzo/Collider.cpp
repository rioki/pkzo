// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Collider.h"

#include <bullet/btBulletDynamicsCommon.h>

#include "btutils.h"
#include "Engine.h"
#include "PhysicSystem.h"

namespace pkzo
{
    Collider::~Collider() = default;

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

    std::shared_ptr<btRigidBody> Collider::get_rigid_body()
    {
        if (rigid_body == nullptr)
        {
            motion_state = std::make_shared<btDefaultMotionState>(to_bt(get_world_transform()));
            collision_shape = get_collision_shape();
            rigid_body = std::make_unique<btRigidBody>(0.0f, motion_state.get(), collision_shape.get());
        }
        return rigid_body;
    }
}
