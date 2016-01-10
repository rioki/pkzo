
#include "SceneNode.h"

namespace pkzo
{
    SceneNode::SceneNode()
    : parent(nullptr), position(0.0f), orientation(0.0f, 0.0f, 0.0f, 1.0f) {}

    SceneNode::~SceneNode() {}

    void SceneNode::set_position(const Vector3& value)
    {
        position = value;
    }

    const Vector3& SceneNode::get_position() const
    {
        return position;
    }

    Vector3 SceneNode::get_world_position() const
    {
        if (parent)
        {
            Quaternion pwq = parent->get_world_orientation();
            return parent->get_world_position() + transform(pwq, position);
        }
        else
        {
            return position;
        }
    }

    void SceneNode::set_orientation(const Quaternion& value)
    {
        orientation = value;
    }

    const Quaternion& SceneNode::get_orientation() const
    {
        return orientation;
    }

    Quaternion SceneNode::get_world_orientation() const
    {
        if (parent)
        {
            return parent->get_world_orientation() * orientation;
        }
        else
        {
            return orientation;
        }
    }

    void SceneNode::update(float t, float dt) {}
}
