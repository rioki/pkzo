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
class btMotionState;
class btCollisionShape;
class btRigidBody;

namespace pkzo
{
    class Engine;
    class SceneNode;
    class Body;
    class Geometry;
    class BoxGeometry;
    class PhysicDebugDrawer;

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

        struct RigidBodyData
        {
            std::unique_ptr<btMotionState> motion_state;
            std::unique_ptr<btCollisionShape> shape;
            std::unique_ptr<btRigidBody> body;
        };
        std::map<SceneNode*, RigidBodyData> bodies;

        void add(Body* body);
        void add(BoxGeometry* body);
        void remove(SceneNode* body);

    friend class Body;
    friend class BoxGeometry;
    };
}

#endif
