// pkzo
// Copyright 2010-2024 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once
#include <vector>
#include <ranges>

#include <rex/managed_ptr.h>

#include "Node.h"
#include "Bounds.h"

namespace pkzo
{
    template <typename Type>
    class NodeGroup : public Node<Type>
    {
    public:
        using Matrix = Node<Type>::Matrix;
        using Bounds = Node<Type>::Bounds;

        NodeGroup() noexcept
        : NodeGroup(Matrix(1.0f)) {}

        explicit NodeGroup(const Matrix& _transform) noexcept
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
            add_node_impl(rex::wrap_managed(node));
        }

        void add_node(std::unique_ptr<Node<Type>>&& node) noexcept
        {
            add_node_impl(std::move(node));
        }

        void remove_node(Node<Type>& node) noexcept
        {
            remove_node(&node);
        }

        void remove_node(Node<Type>* node) noexcept
        {
            check(node != nullptr);
            check(node->get_parent() == this);

            auto i = std::ranges::find_if(nodes, [&node] (const auto& child) {
                return child.get() == node;
            });

            if (Node<Type>::is_active())
            {
                node->deactivate();
            }

            node->parent = nullptr;

            check(i != end(nodes));
            nodes.erase(i);

            remove_node_signal.emit();
        }

        std::vector<Node<Type>*> get_nodes() noexcept
        {
            return nodes
                 | std::views::transform([](auto& child) { return child.get(); })
                 | rex::ranges::to<std::vector<Node<Type>*>>();
        }

        std::vector<const Node<Type>*> get_nodes() const noexcept
        {
            return nodes
                 | std::views::transform([](auto& child) { return child.get(); })
                 | rex::ranges::to<std::vector<const Node<Type>*>>();
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

        rex::connection on_add_node(const std::function<void ()>& cb) noexcept
        {
            return add_node_signal.connect(cb);
        }

        rex::signal<>& get_add_node_signal() noexcept
        {
            return add_node_signal;
        }

        rex::connection on_remove_node(const std::function<void ()>& cb) noexcept
        {
            return remove_node_signal.connect(cb);
        }

        rex::signal<>& get_remove_node_signal() noexcept
        {
            return remove_node_signal;
        }

        Bounds get_bounds() const noexcept override
        {
            Bounds bounds;
            for (auto& node : nodes)
            {
                bounds = merge(bounds, node->get_transform() * node->get_bounds());
            }
            return bounds;
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

        void update(std::chrono::milliseconds dt) override
        {
            for (const auto& node : nodes)
            {
                node->update(dt);
            }
        }

    private:
        std::vector<rex::managed_ptr<Node<Type>>> nodes;
        rex::signal<>                             add_node_signal;
        rex::signal<>                             remove_node_signal;

        void add_node_impl(rex::managed_ptr<Node<Type>>&& node) noexcept
        {
            check(node != nullptr);
            check(node->get_parent() == nullptr);

            node->parent = this;
            if (Node<Type>::is_active())
            {
                node->activate();
            }
            nodes.push_back(std::move(node));

            add_node_signal.emit();
        }
    };
}