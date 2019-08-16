// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_CAPSULE_COLLIDER_H_
#define _PKZO_CAPSULE_COLLIDER_H_

#include "Collider.h"

class btCapsuleShape;

namespace pkzo
{
    //! Capsule Collider
    class PKZO_EXPORT CapsuleCollider : public Collider
    {
    public:
        //! Create capsule collider.
        CapsuleCollider(float radius, float height);
        //! Get the diameter.
        float get_diameter() const;
        //! Get the height;
        float get_height() const;

    protected:
        std::shared_ptr<btCollisionShape> get_collision_shape() override;

    private:
        float                           diameter;
        float                           height;
        std::shared_ptr<btCapsuleShape> collision_shape;
    };
}

#endif
