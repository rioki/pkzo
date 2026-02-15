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

namespace pkzo2d
{
    class Scene;

    class PKZO2D_EXPORT Group : public Node
    {
    public:
        using Node::Specs;

        Group(Specs specs);

        ~Group();

        template <typename NodeT>
        NodeT* add(NodeT::Specs specs);

        void remove(Node* node);

        std::vector<Node*> get_nodes();

        void handle_mouse_button_down(glm::vec2& pos, MouseButton button) override;
        void handle_mouse_button_up(glm::vec2& pos, MouseButton button) override;

        void update(float dt) override;

    private:
        std::vector<std::shared_ptr<Node>> nodes;
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
}
