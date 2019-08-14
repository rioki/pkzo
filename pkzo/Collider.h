// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_COLLIDER_H_
#define _PKZO_COLLIDER_H_

#include "SceneNode.h"

class btCollisionShape;

namespace pkzo
{
    class Body;

    //! Physics Collider Base
    class PKZO_EXPORT Collider : public SceneNode
    {
    public:
        void activate() override;
        void deactivate() override;
    protected:
        virtual std::shared_ptr<btCollisionShape> get_collision_shape() = 0;

    private:

        friend class PhysicSystem;
        friend std::tuple<std::shared_ptr<btCollisionShape>, glm::mat4> create_shape(Body* body); // DELETEME
    };
}

#endif
