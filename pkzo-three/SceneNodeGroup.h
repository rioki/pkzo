//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#pragma once
#include <pkzo/config.h>
#include <memory>
#include <vector>

#include "SceneNode.h"

namespace pkzo::three
{
    //! Scene Node
    class PKZO_EXPORT SceneNodeGroup : public SceneNode
    {
    public:
        SceneNodeGroup() noexcept = default;
        SceneNodeGroup(const glm::mat4& transform) noexcept;

        //! Add child to group.
        void add_child(std::shared_ptr<SceneNode> child) noexcept;
        //! Remove child to group.
        void remove_child(std::shared_ptr<SceneNode> child) noexcept;

        //! Get all direct children of this node.
        //! @{
        const std::vector<std::shared_ptr<SceneNode>>& get_children() noexcept;
        std::vector<std::shared_ptr<const SceneNode>> get_children() const noexcept;
        //! @}

    private:
        std::vector<std::shared_ptr<SceneNode>> children;
    };
}
