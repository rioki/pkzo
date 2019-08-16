// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SphereCollider.h"

#include <bullet/btBulletDynamicsCommon.h>
#include "btutils.h"

namespace pkzo
{
    SphereCollider::SphereCollider(float d)
    : diameter(d) {}

    float SphereCollider::get_diameter() const
    {
        return diameter;
    }

    std::shared_ptr<btCollisionShape> SphereCollider::get_collision_shape()
    {
        if (collision_shape == nullptr)
        {
            auto radius = diameter / 2.0f;
            collision_shape = std::make_shared<btSphereShape>(radius);
            collision_shape->setUserPointer(this);
        }
        return collision_shape;
    }
}
