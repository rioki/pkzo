// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_COLLIDER_H_
#define _PKZO_COLLIDER_H_

#include "SceneNode.h"

class btMotionState;
class btCollisionShape;
class btRigidBody;

namespace pkzo
{
    class Body;

    //! Physics Collider Base
    class PKZO_EXPORT Collider : public SceneNode
    {
    public:
        ~Collider();
        void activate() override;
        void deactivate() override;
    protected:


        virtual std::shared_ptr<btCollisionShape> get_collision_shape() = 0;

    private:
        std::shared_ptr<btMotionState>    motion_state;
        std::shared_ptr<btCollisionShape> collision_shape;
        std::shared_ptr<btRigidBody>      rigid_body;

        std::shared_ptr<btRigidBody> get_rigid_body();

        friend class PhysicSystem;
        friend class Body;
    };
}

#endif
