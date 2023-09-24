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

#include "SceneNode.h"

#include "Scene.h"

namespace pkzo::three
{
    SceneNode::SceneNode() = default;

    SceneNode::SceneNode(const glm::mat4& init_transform, SceneNode* parent)
    : transform(init_transform), parent(parent) {}

    glm::mat4 SceneNode::get_transform() const noexcept
    {
        return transform;
    }

    glm::mat4 SceneNode::get_global_transform() const noexcept
    {
        if (parent)
        {
            return parent->get_global_transform() * transform;
        }
        return transform;
    }

    void SceneNode::set_transform(const glm::mat4& new_transform) noexcept
    {
        transform = new_transform;
    }

    SceneNode* SceneNode::get_parent() const noexcept
    {
        return parent;
    }

    void SceneNode::set_parent(SceneNode* new_parent) noexcept
    {
        parent = new_parent;
    }

    Scene* SceneNode::get_scene() noexcept
    {
        auto this_scene = dynamic_cast<Scene*>(this);
        if (this_scene)
        {
            return this_scene;
        }

        if (parent)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    const Scene* SceneNode::get_scene() const noexcept
    {
        return const_cast<SceneNode*>(this)->get_scene();
    }
}
