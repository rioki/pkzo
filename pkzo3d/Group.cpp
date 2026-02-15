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

#include "Group.h"

namespace pkzo3d
{
    Group::Group(Specs specs)
    : Node(std::move(specs)) {}

    Group::~Group() = default;

    void Group::remove(Node* node)
    {
        std::erase_if(nodes, [node] (const auto& ptr) { return node == ptr.get(); } );
    }

    std::vector<Node*> Group::get_nodes()
    {
        auto result = std::vector<Node*>{};

        for (const auto& ptr : nodes)
        {
            result.push_back(ptr.get());
        }

        return result;
    }

    Bounds Group::get_bounds() const
    {
        Bounds bounds;
        for (auto& node : nodes)
        {
            bounds = merge(bounds, node->get_transform() * node->get_bounds());
        }
        return bounds;
    }

    void Group::update(float dt)
    {
        auto nodes_copy = nodes;
        for (const auto& ptr : nodes_copy)
        {
            ptr->update(dt);
        }
    }
}
