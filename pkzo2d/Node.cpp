// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Node.h"

#include "Screen.h"

namespace pkzo2d
{
    Node::Node(Specs specs)
    : parent(specs.parent), transform(specs.transform)
    {
        if (parent != nullptr)
        {
            parent_move_slot = parent->on_move([this] () {
                move_signal.emit();
            });
        }
    }

    Node::~Node() = default;

    Screen* Node::get_screen()
    {
        if (parent != nullptr)
        {
            return parent->get_screen();
        }
        else
        {
            return dynamic_cast<Screen*>(this);
        }
    }

    const Screen* Node::get_screen() const
    {
        return const_cast<Node*>(this)->get_screen();
    }

    Node* Node::get_parent()
    {
        return parent;
    }

    const Node* Node::get_parent() const
    {
        return parent;
    }

    void Node::set_transform(const glm::mat3& value)
    {
        transform = value;
        move_signal.emit();
    }

    const glm::mat3& Node::get_transform() const
    {
        return transform;
    }

    glm::mat3 Node::get_global_transform() const
    {
        if (parent != nullptr)
        {
            return parent->get_global_transform() * transform;
        }
        else
        {
            return transform;
        }
    }

    rsig::connection Node::on_move(const std::function<void ()>& handler)
    {
        return move_signal.connect(handler);
    }

    void Node::handle_mouse_button_down(glm::vec2 pos, MouseButton button) {}
    void Node::handle_mouse_button_up(glm::vec2 pos, MouseButton button) {}

    void Node::update(float dt) {}
}
