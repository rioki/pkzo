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

        for (auto& [node, body] : bodies)
        {
            node->set_transform(to_glm(body.body->getWorldTransform()));
        }

        if (debug_drawer)
        {
            world->debugDrawWorld();
        }
    }

    std::tuple<std::shared_ptr<btCollisionShape>, glm::mat4> create_shape(Body* body)
    {
        for (auto& node : body->get_nodes())
        {
            auto collider = std::dynamic_pointer_cast<Collider>(node);
            if (collider)
            {
                return std::make_tuple(collider->get_collision_shape(), collider->get_transform());
            }
        }
        throw std::logic_error("Body has no collision shape.");
    }

    void PhysicSystem::add(Body* body)
    {
        auto [shape, offset] = create_shape(body);

        auto interia = btVector3{};
        shape->calculateLocalInertia(body->get_mass(), interia);

        auto motion_state = std::make_unique<btDefaultMotionState>(to_bt(body->get_world_transform()), to_bt(offset));

        auto btBody = std::make_unique<btRigidBody>(body->get_mass(), motion_state.get(), shape.get(), interia);
        btBody->setUserPointer(body);

        world->addRigidBody(btBody.get(), stdex::to_int(CollisionType::DYNAMIC), stdex::to_int(CollisionType::DYNAMIC | CollisionType::STATIC));

        bodies[body] = {move(motion_state), move(shape), move(btBody)};
    }

    void PhysicSystem::add(Collider* collider)
    {
        if (dynamic_cast<Body*>(collider->get_parent()) == nullptr)
        {
            auto motion_state = std::make_unique<btDefaultMotionState>(to_bt(collider->get_world_transform()));
            auto shape = collider->get_collision_shape();
            auto body = std::make_unique<btRigidBody>(0.0f, motion_state.get(), shape.get());

            world->addRigidBody(body.get(), stdex::to_int(CollisionType::STATIC), stdex::to_int(CollisionType::DYNAMIC));

            bodies[collider] = {move(motion_state), move(shape), move(body)};
        }
    }

    void PhysicSystem::remove(SceneNode* node)
    {
        auto i = bodies.find(node);
        if (i != end(bodies))
        {
            world->removeRigidBody(i->second.body.get());
            bodies.erase(i);
        }
    }
}
