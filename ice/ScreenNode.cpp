// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "ScreenNode.h"
#include "Screen.h"

namespace ice
{
    ScreenNode::ScreenNode(const glm::mat3& _transform) noexcept
    : transform(_transform) {}

    ScreenNode* ScreenNode::get_parent() noexcept
    {
        return parent;
    }

    const ScreenNode* ScreenNode::get_parent() const noexcept
    {
        return parent;
    }

    Screen* ScreenNode::get_screen() noexcept
    {
        return find_ancestor<Screen>();
    }

    const Screen* ScreenNode::get_screen() const noexcept
    {
        return find_ancestor<Screen>();
    }

    void ScreenNode::set_transform(const glm::mat3& value) noexcept
    {
        transform = value;
        move_signal.emit();
    }

    const glm::mat3& ScreenNode::get_transform() const noexcept
    {
        return transform;
    }

    glm::mat3 ScreenNode::get_world_transform() const noexcept
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

    rsig::connection ScreenNode::on_move(const std::function<void ()>& cb) noexcept
    {
        return move_signal.connect(cb);
    }

    rsig::signal<>& ScreenNode::get_move_signal() noexcept
    {
        return move_signal;
    }

    void ScreenNode::activate() {}

    void ScreenNode::deactivate() {}
}
