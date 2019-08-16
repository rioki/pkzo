// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SPHERE_COLLIDER_H_
#define _PKZO_SPHERE_COLLIDER_H_

#include "Collider.h"

class btSphereShape;

namespace pkzo
{
    //! Sphere Collider
    class PKZO_EXPORT SphereCollider : public Collider
    {
    public:
        //! Create sphere collider.
        SphereCollider(float diameter);
        //! Get the diameter.
        float get_diameter() const;

    protected:
        std::shared_ptr<btCollisionShape> get_collision_shape() override;

    private:
        float                          diameter;
        std::shared_ptr<btSphereShape> collision_shape;
    };
}

#endif
