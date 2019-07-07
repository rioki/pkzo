// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "ScreenNode.h"

namespace pkzo
{
    ScreenNode::ScreenNode(const glm::vec2& p, const glm::vec2& s)
    : position(p), size(s) {}

    ScreenNode::~ScreenNode() = default;

    void ScreenNode::set_position(const glm::vec2& value)
    {
        position = value;
    }

    const glm::vec2& ScreenNode::get_position() const
    {
        return position;
    }

    void ScreenNode::set_size(const glm::vec2& value)
    {
        size = value;
    }

    const glm::vec2& ScreenNode::get_size() const
    {
        return size;
    }

    void ScreenNode::draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) {}
}
