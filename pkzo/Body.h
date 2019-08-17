// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_BODY_H_
#define _PKZO_BODY_H_

#include "SceneNodeGroup.h"

class btMotionState;
class btCollisionShape;
class btRigidBody;

namespace pkzo
{
    //! Physical body
    class PKZO_EXPORT Body : public SceneNodeGroup
    {
    public:
        //! Construct body.
        Body(float mass);

        ~Body();

        //! Set the bodies mass.
        void set_mass(float value);

        //! Get the bodies mass.
        float get_mass() const;

        //! Apply impulse to the body.
        void apply_impulse(const glm::vec3& value);
        //! Apply force to the body.
        void apply_force(const glm::vec3& value);

        void activate() override;
        void deactivate() override;

    private:
        float mass;
        std::shared_ptr<btMotionState>    motion_state;
        std::shared_ptr<btCollisionShape> collision_shape;
        std::shared_ptr<btRigidBody>      rigid_body;

        glm::vec3 acumulated_impulse = {0.0f, 0.0f, 0.0f};
        glm::vec3 force = {0.0f, 0.0f, 0.0f};

        std::shared_ptr<btRigidBody> get_rigid_body();
        void sync_physics();

    friend class PhysicSystem;
    };
}

#endif
