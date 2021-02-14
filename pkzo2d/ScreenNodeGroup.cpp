//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "ScreenNodeGroup.h"

namespace pkzo2d
{
    ScreenNodeGroup::ScreenNodeGroup() = default;
    ScreenNodeGroup::~ScreenNodeGroup() = default;

    void ScreenNodeGroup::set_position(const glm::vec2& value) noexcept
    {
        position = value;
    }

    const glm::vec2& ScreenNodeGroup::get_position() const noexcept
    {
        return position;
    }

    void ScreenNodeGroup::add_node(const std::shared_ptr<ScreenNode>& node) noexcept
    {
        assert(node);
        assert(node->parent == nullptr);
        node->parent = this;
        nodes.push_back(node);
    }

    void ScreenNodeGroup::remove_nodes(const std::shared_ptr<ScreenNode>& node) noexcept
    {
        assert(node);
        assert(node->parent == this);
        auto i = find(begin(nodes), end(nodes), node);
        assert(i != end(nodes));
        nodes.erase(i);
        node->parent = nullptr;
    }

    const std::list<std::shared_ptr<ScreenNode>>& ScreenNodeGroup::get_nodes() noexcept
    {
        return nodes;
    }

    std::list<std::shared_ptr<const ScreenNode>> ScreenNodeGroup::get_nodes() const noexcept
    {
        return {begin(nodes), end(nodes)};
    }

    void ScreenNodeGroup::handle_mouse_button_down(MouseButton button, glm::vec2 pos)
    {
        auto new_pos = pos - position;
        for (const auto& node : nodes)
        {
            node->handle_mouse_button_down(button, new_pos);
        }
    }

    void ScreenNodeGroup::handle_mouse_button_up(MouseButton button, glm::vec2 pos)
    {
        auto new_pos = pos - position;
        for (const auto& node : nodes)
        {
            node->handle_mouse_button_up(button, new_pos);
        }
    }

    void ScreenNodeGroup::handle_mouse_move(glm::vec2 pos, glm::vec2 rel)
    {
        auto new_pos = pos - position;
        for (const auto& node : nodes)
        {
            node->handle_mouse_move(new_pos, rel);
        }
    }

    void ScreenNodeGroup::handle_key_down(KeyMod mod, Key key)
    {
        for (const auto& node : nodes)
        {
            node->handle_key_down(mod, key);
        }
    }

    void ScreenNodeGroup::handle_key_up(KeyMod mod, Key key)
    {
        for (const auto& node : nodes)
        {
            node->handle_key_up(mod, key);
        }
    }

    void ScreenNodeGroup::handle_text(const std::string_view text)
    {
        for (const auto& node : nodes)
        {
            node->handle_text(text);
        }
    }

    void ScreenNodeGroup::render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept
    {
        auto new_offset = offset + position;
        for (const auto& node : nodes)
        {
            node->render(renderer, new_offset);
        }
    }
}
