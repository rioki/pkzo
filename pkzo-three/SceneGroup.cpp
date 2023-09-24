// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "SceneGroup.h"

namespace pkzo::three
{
    template <typename T>
    static void no_delete(T*) noexcept {}

    SceneGroup::SceneGroup() noexcept = default;

    SceneGroup::SceneGroup(const glm::mat4& init_transform) noexcept
    : SceneNode(init_transform) {}

    SceneGroup::~SceneGroup()
    {
        for (auto& node : nodes)
        {
            if (node)
            {
                node->set_parent(nullptr);
            }
        }
    }

    void SceneGroup::add_node(std::shared_ptr<SceneNode> node) noexcept
    {
        node->set_parent(this);
        nodes.push_back(std::move(node));
    }

    void SceneGroup::add_node(SceneNode& node) noexcept
    {
        node.set_parent(this);
        nodes.emplace_back(&node, no_delete<SceneNode>);
    }

    void SceneGroup::remove_node(const std::shared_ptr<SceneNode>& node) noexcept
    {
        node->set_parent(nullptr);
        auto it = std::ranges::find(nodes, node);
        if (it != nodes.end())
        {
            nodes.erase(it);
        }
    }

    void SceneGroup::remove_node(SceneNode& node) noexcept
    {
        node.set_parent(nullptr);
        auto it = std::ranges::find_if(nodes, [&node](const auto& n) { return n.get() == &node; });
        if (it != nodes.end())
        {
            nodes.erase(it);
        }
    }

    const std::vector<std::shared_ptr<SceneNode>>& SceneGroup::get_nodes() noexcept
    {
        return nodes;
    }

    std::vector<std::shared_ptr<const SceneNode>> SceneGroup::get_nodes() const noexcept
    {
        return std::vector<std::shared_ptr<const SceneNode>>(nodes.begin(), nodes.end());
    }
}