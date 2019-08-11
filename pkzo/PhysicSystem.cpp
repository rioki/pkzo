// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "PhysicSystem.h"

#include <glm/gtc/type_ptr.hpp>
#include <bullet/btBulletDynamicsCommon.h>

#include "stdex.h"
#include "Engine.h"
#include "Body.h"
#include "BoxGeometry.h"
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

    btTransform to_bt(const glm::mat4& trans)
    {
        auto result = btTransform{};
        result.setFromOpenGLMatrix(glm::value_ptr(trans));
        return result;
    }

    glm::mat4 to_glm(const btTransform& trans)
    {
        auto result = glm::mat4(1.0f);
        trans.getOpenGLMatrix(glm::value_ptr(result));
        return result;
    }

    btVector3 to_bt(const glm::vec3& vec)
    {
        return {vec.x, vec.y, vec.z};
    }

    glm::vec3 to_glm(const btVector3& vec)
    {
        return {vec[0], vec[1], vec[2]};
    }

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
        /*auto dd = engine.get_system<DebugDrawer>();
        if (dd)
        {
            debug_drawer = std::make_unique<PhysicDebugDrawer>(dd);
            debug_drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb);
            world->setDebugDrawer(debug_drawer.get());
        }*/
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

    std::tuple<std::unique_ptr<btCollisionShape>, glm::mat4> create_shape(Body* body)
    {
        for (auto& node : body->get_nodes())
        {
            auto box = std::dynamic_pointer_cast<BoxGeometry>(node);
            if (box)
            {
                return std::make_tuple(std::make_unique<btBoxShape>(to_bt(box->get_size() / 2.0f)), box->get_transform());
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

    void PhysicSystem::add(BoxGeometry* box)
    {
        if (box->get_parent() == nullptr) // TODO convert check to body
        {
            auto motion_state = std::make_unique<btDefaultMotionState>(to_bt(box->get_world_transform()));
            auto shape = std::make_unique<btBoxShape>(to_bt(box->get_size() / 2.0f));
            auto body = std::make_unique<btRigidBody>(0.0f, motion_state.get(), shape.get());
            body->setUserPointer(box);

            world->addRigidBody(body.get(), stdex::to_int(CollisionType::STATIC), stdex::to_int(CollisionType::DYNAMIC));

            bodies[box] = {move(motion_state), move(shape), move(body)};
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
