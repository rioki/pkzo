// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SCENE_NODE_GROUP_H_
#define _PKZO_SCENE_NODE_GROUP_H_

#include "SceneNode.h"

namespace pkzo
{
    class PKZO_EXPORT SceneNodeGroup : public SceneNode
    {
    public:

        //! Add a node to the group.
        void add_node(const std::shared_ptr<SceneNode>& node);

        //! Remove a node from the group.
        void remove_node(const std::shared_ptr<SceneNode>& node);

        //! Get the nodes in the group.
        const std::list<std::shared_ptr<SceneNode>>& get_nodes();
        //! Get the nodes in the group.
        std::list<std::shared_ptr<const SceneNode>> get_nodes() const;
        //! Get the node of a specific type.
        template <typename NodeT>
        std::list<std::shared_ptr<NodeT>> get_nodes();
        //! Get the node of a specific type.
        template <typename NodeT>
        std::list<std::shared_ptr<const NodeT>> get_nodes() const;


        void enqueue(RenderQueue& queue) const override;
        void activate() override;
        void deactivate() override;
        void update(float dt) override;

    private:
        std::list<std::shared_ptr<SceneNode>> nodes;
    };

    template <typename NodeT>
    std::list<std::shared_ptr<NodeT>> SceneNodeGroup::get_nodes()
    {
        auto result = std::list<std::shared_ptr<NodeT>>{};

        for (auto& node : nodes)
        {
            auto rnode = std::dynamic_pointer_cast<NodeT>(node);
            if (rnode)
            {
                result.push_back(rnode);
            }
        }

        return result;
    }

    template <typename NodeT>
    std::list<std::shared_ptr<const NodeT>> SceneNodeGroup::get_nodes() const
    {
        auto nodes  = const_cast<SceneNodeGroup*>(this)->get_nodes<NodeT>();
        return {begin(nodes), end(nodes)};
    }
}

#endif
