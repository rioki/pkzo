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

#pragma once
#include <pkzo/config.h>

#include <vector>
#include <memory>

#include "SceneNode.h"

namespace pkzo::three
{
    //! SceneGroup class extends SceneNode to manage a collection of child nodes.
    class PKZO_EXPORT SceneGroup : public SceneNode
    {
    public:
        ~SceneGroup();

        //! Adds a node to the group with ownership.
        //!
        //! @param node Shared pointer to the node.
        void add_node(std::shared_ptr<SceneNode> node);

        //! Adds a node to the group as a non-owning shared reference.
        //!
        //! @param node Reference to the node.
        void add_node(SceneNode& node);

        //! Removes a node from the group.
        //!
        //! @param node Shared pointer to the node to remove.
        void remove_node(const std::shared_ptr<SceneNode>& node);

        //! Removes a node from the group by reference.
        //!
        //! @param node Reference to the node to remove.
        void remove_node(SceneNode& node);

        //! Gets the nodes within the group.
        //!
        //! @return Constant reference to the vector of shared pointers to the child nodes.
        const std::vector<std::shared_ptr<SceneNode>>& get_nodes();

        //! Gets the nodes within the group.
        //!
        //! @return Vector of shared pointers to the const child nodes.
        std::vector<std::shared_ptr<const SceneNode>> get_nodes() const;

    private:
        std::vector<std::shared_ptr<SceneNode>> nodes;
    };
}