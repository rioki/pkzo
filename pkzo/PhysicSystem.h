// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_PHYSIC_SYSTEM_H_
#define _PKZO_PHYSIC_SYSTEM_H_

#include "System.h"
#include <memory>
#include <map>

class btBroadphaseInterface;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
class btDynamicsWorld;

namespace pkzo
{
    class Engine;
    class SceneNode;
    class Body;
    class Collider;
    class PhysicDebugDrawer;
    class Mesh;

    //! Physic system
    class PhysicSystem : public System
    {
    public:
        PhysicSystem(Engine& engine);
        ~PhysicSystem();

        void tick(float dt) override;

    private:
        Engine& engine;

        std::unique_ptr<btBroadphaseInterface>    broadphase;
        std::unique_ptr<btCollisionConfiguration> collisionConfiguration;
        std::unique_ptr<btCollisionDispatcher>    dispatcher;
        std::unique_ptr<btConstraintSolver>       solver;
        std::unique_ptr<btDynamicsWorld>          world;
        std::unique_ptr<PhysicDebugDrawer>        debug_drawer;

        std::list<Body*> bodies;

        void add(Body* body);
        void add(Collider* collider);
        void remove(Body* body);
        void remove(Collider* collider);

    friend class Body;
    friend class Collider;
    friend class MeshCollider;
    };
}

#endif
