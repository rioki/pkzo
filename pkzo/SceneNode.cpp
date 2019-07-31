// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

#include "dbg.h"

namespace pkzo
{
    SceneNode::SceneNode() = default;
    SceneNode::~SceneNode() = default;

    Scene& SceneNode::get_scene()
    {
        PKZO_ASSERT(scene != nullptr);
        return *scene;
    }

    const Scene& SceneNode::get_scene() const
    {
        PKZO_ASSERT(scene != nullptr);
        return *scene;
    }

    void SceneNode::set_transform(const glm::mat4& value)
    {
        transform = value;
    }

    const glm::mat4& SceneNode::get_transform() const
    {
        return transform;
    }

    void SceneNode::move(const glm::vec3& value)
    {
        transform = glm::translate(transform, value);
    }

    void SceneNode::rotate(float angle, const glm::vec3& axis)
    {
        transform = glm::rotate(transform, angle, axis);
    }

    void SceneNode::enqueue(RenderQueue& queue) const {}
}
