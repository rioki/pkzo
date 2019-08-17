// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "PhysicSystem.h"

#include <glm/gtc/type_ptr.hpp>
#include <bullet/btBulletDynamicsCommon.h>

#include "stdex.h"
#include "btutils.h"
#include "Engine.h"
#include "Body.h"
#include "Collider.h"
#include "DebugDrawer.h"
#include "PhysicDebugDrawer.h"
#include "Mesh.h"

namespace pkzo
{
    enum class CollisionType : int
    {
        NONE = 0,
        STATIC = STDEX_BIT(1),
        DYNAMIC = STDEX_BIT(2),
        ALL = -1
    };
    STDEX_ENUM_BIT_OPERATORS(CollisionType);

    PhysicSystem::PhysicSystem(Engine& e)
    : engine(e)
    {
        broadphase = std::make_unique<btDbvtBroadphase>();
        collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
        dispatcher = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
        solver = std::make_unique<btSequentialImpulseConstraintSolver>();

        world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get());
        world->setGravity(btVector3(0.0f, 0.0f, -9.8f));

        // TODO make this configurable
        auto dd = engine.get_system<DebugDrawer>();
        if (dd)
        {
            debug_drawer = std::make_unique<PhysicDebugDrawer>(dd);
            debug_drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb);
            world->setDebugDrawer(debug_drawer.get());
        }
    }

    PhysicSystem::~PhysicSystem()
    {
        world                   = nullptr;
        debug_drawer            = nullptr;

        solver                  = nullptr;
        dispatcher              = nullptr;
        collisionConfiguration  = nullptr;
        broadphase              = nullptr;
    }

    void PhysicSystem::tick(float dt)
    {
        assert(world);
        world->stepSimulation(dt);

        for (auto body : bodies)
        {
            body->sync_physics();
        }

        if (debug_drawer)
        {
            world->debugDrawWorld();
        }
    }

    void PhysicSystem::add(Body* body)
    {
        auto btBody = body->get_rigid_body();
        world->addRigidBody(btBody.get(), stdex::to_int(CollisionType::DYNAMIC), stdex::to_int(CollisionType::DYNAMIC | CollisionType::STATIC));

        bodies.push_back(body);
    }

    void PhysicSystem::add(Collider* collider)
    {
        if (dynamic_cast<Body*>(collider->get_parent()) == nullptr)
        {
            auto bt_body = collider->get_rigid_body();
            world->addRigidBody(bt_body.get(), stdex::to_int(CollisionType::STATIC), stdex::to_int(CollisionType::DYNAMIC));
        }
    }

    void PhysicSystem::remove(Body* body)
    {
        auto bt_body = body->get_rigid_body();
        world->removeRigidBody(bt_body.get());

        auto i = std::find(begin(bodies), end(bodies), body);
        assert(i != end(bodies));
        bodies.erase(i);
    }

    void PhysicSystem::remove(Collider* collider)
    {
        if (dynamic_cast<Body*>(collider->get_parent()) == nullptr)
        {
            auto bt_body = collider->get_rigid_body();
            world->removeRigidBody(bt_body.get());
        }
    }
}
