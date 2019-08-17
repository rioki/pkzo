// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SceneNode.h"

#include <cassert>
#include <glm/gtc/matrix_transform.hpp>

#include "dbg.h"
#include "Scene.h"

namespace pkzo
{
    SceneNode::~SceneNode() = default;

    Engine& SceneNode::get_engine()
    {
        return get_scene().get_engine();
    }

    Scene& SceneNode::get_scene()
    {
        if (parent)
        {
            return parent->get_scene();
        }
        else
        {
            assert(scene != nullptr);
            return *scene;
        }
    }

    const Scene& SceneNode::get_scene() const
    {
        return const_cast<SceneNode*>(this)->get_scene();
    }

    SceneNode* SceneNode::get_parent()
    {
        return parent;
    }

    const SceneNode* SceneNode::get_parent() const
    {
        return parent;
    }

    void SceneNode::set_transform(const glm::mat4& value)
    {
        transform = value;
    }

    const glm::mat4& SceneNode::get_transform() const
    {
        return transform;
    }

    glm::mat4 SceneNode::get_world_transform() const
    {
        if (parent)
        {
            return parent->get_world_transform() * transform;
        }
        else
        {
            return transform;
        }
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

    void SceneNode::activate() {}

    void SceneNode::deactivate() {}

    void SceneNode::update(float dt) {}
}
