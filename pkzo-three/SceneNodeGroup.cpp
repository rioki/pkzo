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

#include "pch.h"
#include "SceneNodeGroup.h"

#include "Scene.h"

namespace pkzo::three
{
    SceneNodeGroup::SceneNodeGroup(const glm::mat4& t) noexcept
    : SceneNode(t) {}

    void SceneNodeGroup::add_child(std::shared_ptr<SceneNode> child) noexcept
    {
        DBG_ASSERT(child);
        DBG_ASSERT(child->get_parent() == nullptr);

        children.push_back(child);
        child->on_attach(this);

        auto s = find_elder<Scene>();
        if (s)
        {
            child->on_attach_scene(s);
        }
    }

    void SceneNodeGroup::remove_child(std::shared_ptr<SceneNode> child) noexcept
    {
        DBG_ASSERT(child);
        DBG_ASSERT(child->get_parent() == this);

        auto i = find(begin(children), end(children), child);
        DBG_ASSERT(i != end(children));

        auto s = find_elder<Scene>();
        if (s)
        {
            child->on_detach_scene();
        }
        child->on_detach();

        children.erase(i);
    }

    const std::vector<std::shared_ptr<SceneNode>>& SceneNodeGroup::get_children() noexcept
    {
        return children;
    }

    std::vector<std::shared_ptr<const SceneNode>> SceneNodeGroup::get_children() const noexcept
    {
        return {begin(children), end(children)};
    }

    void SceneNodeGroup::on_attach_scene(Scene* scene) noexcept
    {
        SceneNode::on_attach_scene(scene);
        for (auto& child : children)
        {
            child->on_attach_scene(scene);
        }
    }

    void SceneNodeGroup::on_detach_scene() noexcept
    {
        for (auto& child : children)
        {
            child->on_detach_scene();
        }
        SceneNode::on_detach_scene();
    }

    void SceneNodeGroup::update(std::chrono::milliseconds dt) noexcept
    {
        SceneNode::update(dt);
        for (auto& child : children)
        {
            child->update(dt);
        }
    }
}