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

#pragma once
#include "config.h"

#include <memory>
#include <vector>

#include "utils.h"
#include "Node.h"

namespace ice
{
    template <typename Type>
    class NodeGroup : public Node<Type>
    {
    public:
        using Matrix = Node<Type>::Matrix;

        NodeGroup() noexcept
        : NodeGroup(glm::mat4(1.0f)) {}

        NodeGroup(const Matrix& _transform) noexcept
        : Node<Type>(_transform)
        {
            this->on_move([this] () {
                for (const auto& node : nodes)
                {
                    node->get_move_signal().emit();
                }
            });
        }

        void add_node(Node<Type>& node) noexcept
        {
            add_node(std::shared_ptr<Node<Type>>(&node, no_delete<Node<Type>>));
        }

        void add_node(const std::shared_ptr<Node<Type>>& node) noexcept
        {
            assert(node != nullptr);
            assert(node->get_parent() == nullptr);

            node->parent = this;
            nodes.push_back(node);

            auto root = Node<Type>::get_root();
            if (root != nullptr && root->is_active())
            {
                node->activate();
            }

            add_node_signal.emit();
        }

        void remove_node(Node<Type>& node) noexcept
        {
            assert(node.get_parent() == this);

            auto i = std::ranges::find_if(nodes, [&node] (const auto& child) {
                return child.get() == &node;
            });

            auto root = Node<Type>::get_root();
            if (root != nullptr && root->is_active())
            {
                node.deactivate();
            }

            node.parent = nullptr;

            assert(i != end(nodes));
            nodes.erase(i);

            remove_node_signal.emit();
        }

        void remove_node(const std::shared_ptr<Node<Type>>& node) noexcept
        {
            assert(node != nullptr);
            remove_node(*node);
        }

        std::vector<Node<Type>*> get_nodes() noexcept
        {
            return to<std::vector<Node<Type>*>>(std::views::transform(nodes, [] (auto& node) {
                return node.get();
            }));
        }

        std::vector<const Node<Type>*> get_nodes() const noexcept
        {
            return to<std::vector<const Node<Type>*>>(std::views::transform(nodes, [] (auto& node) {
                return node.get();
            }));
        }

        template <typename NodeType>
        std::vector<NodeType*> get_nodes() noexcept
        {
            std::vector<NodeType*> result;

            for (const auto& node : nodes)
            {
                auto n = dynamic_cast<NodeType*>(node.get());
                if (n)
                {
                    result.push_back(n);
                }
            }

            return result;
        }

        template <typename NodeType>
        std::vector<const NodeType*> get_nodes() const noexcept
        {
            std::vector<const NodeType*> result;

            for (const auto& node : nodes)
            {
                auto n = dynamic_cast<const NodeType*>(node.get());
                if (n)
                {
                    result.push_back(n);
                }
            }

            return result;
        }

        rsig::connection on_add_node(const std::function<void ()>& cb) noexcept
        {
            return add_node_signal.connect(cb);
        }

        rsig::signal<>& get_add_node_signal() noexcept
        {
            return add_node_signal;
        }

        rsig::connection on_remove_node(const std::function<void ()>& cb) noexcept
        {
            return remove_node_signal.connect(cb);
        }

        rsig::signal<>& get_remove_node_signal() noexcept
        {
            return remove_node_signal;
        }

        void activate() override
        {
            for (const auto& node : nodes)
            {
                node->activate();
            }
        }

        void deactivate() override
        {
            for (const auto& node : nodes)
            {
                node->deactivate();
            }
        }

    private:
        std::vector<std::shared_ptr<Node<Type>>> nodes;
        rsig::signal<> add_node_signal;
        rsig::signal<> remove_node_signal;
    };
}
