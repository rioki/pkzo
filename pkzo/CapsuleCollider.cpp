// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "CalsuleCollider.h"

#include <bullet/btBulletDynamicsCommon.h>
#include "btutils.h"

namespace pkzo
{
    CapsuleCollider::CapsuleCollider(float d, float h)
    : diameter(d), height(h) {}

    float CapsuleCollider::get_diameter() const
    {
        return diameter;
    }

    float CapsuleCollider::get_height() const
    {
        return height;
    }

    std::shared_ptr<btCollisionShape> CapsuleCollider::get_collision_shape()
    {
        if (collision_shape == nullptr)
        {
            auto radius = diameter / 2.0f;
            collision_shape = std::make_shared<btCapsuleShapeZ>(radius, height - 2.0f * radius);
            collision_shape->setUserPointer(this);
        }
        return collision_shape;
    }
}
