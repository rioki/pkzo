// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "ScreenNodeGroup.h"
#include "Screen.h"

#include "utils.h"

namespace ice
{
    void no_delete(ScreenNode*) {}

    ScreenNodeGroup::ScreenNodeGroup(const glm::mat3& transform) noexcept
    : ScreenNode(transform) {}

    void ScreenNodeGroup::add_node(ScreenNode& node) noexcept
    {
        add_node(std::shared_ptr<ScreenNode>(&node, no_delete));
    }

    void ScreenNodeGroup::add_node(const std::shared_ptr<ScreenNode>& node) noexcept
    {
        assert(node != nullptr);
        assert(node->get_parent() == nullptr);

        node->parent = this;
        nodes.push_back(node);

        auto screen = get_screen();
        if (screen != nullptr && screen->is_active())
        {
            node->activate();
        }
    }

    void ScreenNodeGroup::remove_node(ScreenNode& node) noexcept
    {
        assert(node.get_parent() == this);

        auto i = std::ranges::find_if(nodes, [&node] (const auto& child) {
            return child.get() == &node;
        });

        auto screen = get_screen();
        if (screen != nullptr && screen->is_active())
        {
            node.deactivate();
        }

        node.parent = nullptr;

        assert(i != end(nodes));
        nodes.erase(i);
    }

    void ScreenNodeGroup::remove_node(const std::shared_ptr<ScreenNode>& node) noexcept
    {
        assert(node != nullptr);
        remove_node(*node);
    }

    std::vector<ScreenNode*> ScreenNodeGroup::get_nodes() noexcept
    {
        return to<std::vector<ScreenNode*>>(std::views::transform(nodes, [] (auto& node) {
            return node.get();
        }));
    }

    std::vector<const ScreenNode*> ScreenNodeGroup::get_nodes() const noexcept
    {
        return to<std::vector<const ScreenNode*>>(std::views::transform(nodes, [] (auto& node) {
            return node.get();
        }));
    }

    void ScreenNodeGroup::activate()
    {
        for (const auto& node : nodes)
        {
            node->activate();
        }
    }

    void ScreenNodeGroup::deactivate()
    {
        for (const auto& node : nodes)
        {
            node->deactivate();
        }
    }
}
