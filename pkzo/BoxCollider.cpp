// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "BoxCollider.h"

#include <bullet/btBulletDynamicsCommon.h>
#include "btutils.h"

namespace pkzo
{
    BoxCollider::BoxCollider(const glm::vec3& s)
    : size(s) {}

    const glm::vec3& BoxCollider::get_size() const
    {
        return size;
    }

    std::shared_ptr<btCollisionShape> BoxCollider::get_collision_shape()
    {
        if (collision_shape == nullptr)
        {
            collision_shape = std::make_shared<btBoxShape>(to_bt(size * 0.5f));
            collision_shape->setUserPointer(this);
        }
        return collision_shape;
    }
}
