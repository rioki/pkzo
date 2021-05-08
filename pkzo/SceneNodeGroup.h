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
#include "config.h"
#include <memory>
#include <vector>

#include "SceneNode.h"

namespace pkzo
{
    //! Scene Node
    class PKZO_EXPORT SceneNodeGroup : public SceneNode
    {
    public:
        SceneNodeGroup() noexcept = default;
        SceneNodeGroup(const glm::mat4& transform) noexcept;

        //! Add child to group.
        virtual void add_child(std::shared_ptr<SceneNode> child) noexcept;
        //! Remove child to group.
        virtual void remove_child(std::shared_ptr<SceneNode> child) noexcept;

        //! Get all direct children of this node.
        //! @{
        const std::vector<std::shared_ptr<SceneNode>>& get_children() noexcept;
        std::vector<std::shared_ptr<const SceneNode>> get_children() const noexcept;
        //! @}

        //! //! Get all children of specific type.
        //! @{
        template <typename NodeT>
        std::vector<std::shared_ptr<NodeT>> find_children() noexcept;
        template <typename NodeT>
        std::vector<std::shared_ptr<const SceneNode>> find_children() const noexcept;
        //! @}

    protected:
        void on_attach_scene(Scene* scene) noexcept override;
        void on_detach_scene() noexcept override;
        void update(std::chrono::milliseconds dt) noexcept override;

    private:
        std::vector<std::shared_ptr<SceneNode>> children;
    };

    template <typename NodeT>
    void _find_children(std::vector<std::shared_ptr<NodeT>>& nodes, const std::shared_ptr<SceneNode>& node)
    {
         auto n = std::dynamic_pointer_cast<NodeT>(node);
         if (n)
         {
             nodes.push_back(n);
         }
         auto g = std::dynamic_pointer_cast<SceneNodeGroup>(node);
         if (g)
         {
             for (auto& child : g->get_children())
             {
                 _find_children<NodeT>(nodes, child);
             }
         }
    }

    template <typename NodeT>
    std::vector<std::shared_ptr<NodeT>> SceneNodeGroup::find_children() noexcept
    {
        std::vector<std::shared_ptr<NodeT>> result;
        for (auto& child : children)
        {
            _find_children(result, child);
        }
        return result;
    }

    template <typename NodeT>
    std::vector<std::shared_ptr<const SceneNode>> SceneNodeGroup::find_children() const noexcept
    {
        auto result = const_cast<SceneNodeGroup*>(this)->find_children<NodeT>();
        return {begin(result), end(result)};
    }


}
