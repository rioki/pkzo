// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
        auto this_screen = dynamic_cast<Screen*>(this);
        if (this_screen)
        {
            return this_screen;
        }

        return find_ancestor<Screen>();
    }

    const Screen* ScreenNode::get_screen() const noexcept
    {
        return const_cast<ScreenNode*>(this)->get_screen();
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
