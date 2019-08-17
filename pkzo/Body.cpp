// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Body.h"

#include <bullet/btBulletDynamicsCommon.h>

#include "btutils.h"
#include "Engine.h"
#include "PhysicSystem.h"
#include "Collider.h"

namespace pkzo
{
    Body::Body(float m)
    : mass(m) {}

    Body::~Body() = default;

    void Body::set_mass(float value)
    {
        mass = value;
    }

    float Body::get_mass() const
    {
        return mass;
    }

    void Body::apply_impulse(const glm::vec3& value)
    {
        acumulated_impulse += value;
    }

    void Body::apply_force(const glm::vec3& value)
    {
        force = value;
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

    std::shared_ptr<btRigidBody> Body::get_rigid_body()
    {
        if (rigid_body == nullptr)
        {
            auto colliders = get_nodes<Collider>();
            assert(colliders.size() < 2); // currently only one collider per body is supported
            if (colliders.empty())
            {
                throw std::logic_error("No collider for body.");
            }

            auto collider = colliders.front();

            motion_state = std::make_shared<btDefaultMotionState>(to_bt(get_world_transform()), to_bt(collider->get_transform()));
            collision_shape = collider->get_collision_shape();

            auto interia = btVector3{};
            collision_shape->calculateLocalInertia(mass, interia);

            rigid_body = std::make_unique<btRigidBody>(mass, motion_state.get(), collision_shape.get(), interia);
        }
        return rigid_body;
    }

    void Body::sync_physics()
    {
        assert(rigid_body);
        set_transform(to_glm(rigid_body->getWorldTransform()));

        rigid_body->applyCentralImpulse(to_bt(acumulated_impulse));
        acumulated_impulse = {0.0f, 0.0f, 0.0f};

        rigid_body->applyCentralForce(to_bt(force));
    }
}
