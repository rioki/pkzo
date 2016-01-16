
#include "SceneNodeGroup.h"

namespace pkzo
{
    SceneNodeGroup::SceneNodeGroup() {}

    SceneNodeGroup::~SceneNodeGroup() {}

    void SceneNodeGroup::add_node(SceneNode& node)
    {
        nodes.push_back(&node);
        node.parent = this;
    }

    void SceneNodeGroup::remove_node(SceneNode& node)
    {
        auto i = std::find(nodes.begin(), nodes.end(), &node);
        if (i == nodes.end())
        {
            throw std::logic_error("node not in group");
        }
        nodes.erase(i);
        node.parent = nullptr;
    }

    void SceneNodeGroup::update(float t, float dt)
    {
        for (SceneNode* node : nodes)
        {
            node->update(t, dt);
        }
    }

    void SceneNodeGroup::enqueue(SceneRenderer& renderer) const
    {
        for (const SceneNode* node : nodes)
        {
            node->enqueue(renderer);
        }
    }
}