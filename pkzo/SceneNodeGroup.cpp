// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SceneNodeGroup.h"

#include "dbg.h"

namespace pkzo
{
    void SceneNodeGroup::add_node(const std::shared_ptr<SceneNode>& node)
    {
        PKZO_ASSERT(node->parent == nullptr);
        nodes.push_back(node);
        node->parent = this;
    }

    void SceneNodeGroup::remove_node(const std::shared_ptr<SceneNode>& node)
    {
        PKZO_ASSERT(node->parent == this);
        auto i = std::find(nodes.begin(), nodes.end(), node);
        if (i == nodes.end())
        {
            PKZO_THROW(std::invalid_argument, "Node is not in group.``");
        }
        node->parent = nullptr;
        nodes.erase(i);
    }

    const std::list<std::shared_ptr<SceneNode>>& SceneNodeGroup::get_nodes()
    {
        return nodes;
    }

    std::list<std::shared_ptr<const SceneNode>> SceneNodeGroup::get_nodes() const
    {
        return {begin(nodes), end(nodes)};
    }

    void SceneNodeGroup::update(float dt)
    {
        for (auto& node : nodes)
        {
            node->update(dt);
        }
    }
}

