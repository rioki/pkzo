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

#pragma once

#include <vector>
#include <memory>

#include "Node.h"

namespace pkzo3d
{
    class Scene;

    class PKZO3D_EXPORT Group : public Node
    {
    public:
        using Node::Specs;

        Group(Specs specs);

        ~Group();

        template <typename NodeT>
        NodeT* add(NodeT::Specs specs = {});

        void remove(Node* node);

        std::vector<Node*> get_nodes();

        template <typename NodeT>
        std::vector<NodeT*> find_decendents();
        template <typename NodeT>
        std::vector<const NodeT*> find_decendents() const;

        Bounds get_bounds() const override;

        void update(float dt) override;

    private:
        std::vector<std::shared_ptr<Node>> nodes;

        template <typename NodeT>
        void find_decendent_impl(std::vector<NodeT*>& result);
    };

    template <typename NodeT>
    NodeT* Group::add(NodeT::Specs specs)
    {
        specs.parent = this;
        auto node = std::make_unique<NodeT>(std::move(specs));
        auto ptr = node.get();
        nodes.push_back(std::move(node));
        return ptr;
    }

    template <typename NodeT>
    std::vector<NodeT*> Group::find_decendents()
    {
        auto result = std::vector<NodeT*>{};
        find_decendent_impl<NodeT>(result);
        return result;
    }

    template <typename NodeT>
    std::vector<const NodeT*> Group::find_decendents() const
    {
        auto result = std::vector<const NodeT*>{};
        find_decendent_impl<const NodeT>(result);
        return result;
    }

    template <typename NodeT>
    void Group::find_decendent_impl(std::vector<NodeT*>& result)
    {
        for (const auto& child : nodes)
        {
            auto c = dynamic_cast<NodeT*>(child.get());
            if (c)
            {
                result.push_back(c);
            }
            auto g = dynamic_cast<Group*>(child.get());
            if (g)
            {
                g->find_decendent_impl(result);
            }
        }
    }
}
