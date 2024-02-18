// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Group.h"
#include "Scene.h"

namespace pkzo
{
    PKZO_THREE_REGISTER_TYPE(Group);

    Group::Group() = default;

    Group::Group(glm::mat4 transform)
    : SceneNode(transform) {}

    Group::Group(const Group& other)
    : SceneNode(other)
    {
        for (auto& child : other.children)
        {
            if (child.is_managed())
            {
                add_child(child->clone());
            }
        }
    }

    Group::~Group() = default;

    std::string Group::get_type() const noexcept
    {
        return "Group";
    }

    std::unique_ptr<SceneNode> Group::clone() const noexcept
    {
        return std::make_unique<Group>(*this);
    }

    void Group::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        SceneNode::serialize(j, base_dir);

        auto jchildren = nlohmann::json::array();
        for (auto& child : children)
        {
            if (child.is_managed())
            {
                auto cj = nlohmann::json();
                child->serialize(cj, base_dir);
                jchildren.push_back(cj);
            }
        }
        j["children"] = jchildren;
    }

    void Group::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        SceneNode::deserialize(j, base_dir);

        if (j.contains("children"))
        {
            for (auto& child : j["children"])
            {
                auto type = child.at("type").get<std::string>();
                auto node = SceneNode::create(type);
                node->deserialize(child, base_dir);
                add_child(std::move(node));
            }
        }
    }

    void Group::add_child(SceneNode& child)
    {
        check(child.parent == nullptr);
        child.parent = this;
        children.push_back(rex::wrap_managed(child));

        if (is_active())
        {
            child.activate();
        }
    }

    void Group::add_child(std::unique_ptr<SceneNode> child)
    {
        check(child != nullptr);
        check(child->parent == nullptr);

        auto tmp = child.get();
        child->parent = this;
        children.push_back(std::move(child));

        if (is_active())
        {
            tmp->activate();
        }
    }

    void Group::remove_child(SceneNode& child)
    {
        remove_child(&child);
    }

    void Group::remove_child(SceneNode* child)
    {
        check(child != nullptr);
        check(child->parent == this);
        auto it = std::ranges::find_if(children, [&] (auto& ptr) { return ptr.get() == child; });
        check(it != children.end());

        if (is_active())
        {
            child->deactivate();
        }

        children.erase(it);
        child->parent = nullptr;
    }

    void Group::activate()
    {
        SceneNode::activate();
        for (const auto& child : children)
        {
            child->activate();
        }
    }

    void Group::deactivate()
    {
        for (const auto& child : children)
        {
            child->deactivate();
        }
        SceneNode::deactivate();
    }

    void Group::update(float dt)
    {
        SceneNode::update(dt);
        for (const auto& child : children)
        {
            child->update(dt);
        }
    }

    std::vector<SceneNode*> Group::get_children() noexcept
    {
        return children
               | std::views::transform([](auto& child) { return child.get(); })
               | rex::ranges::to<std::vector<SceneNode*>>();
    }

    std::vector<const SceneNode*> Group::get_children() const noexcept
    {
        return children
               | std::views::transform([](const auto& child) { return child.get(); })
               | rex::ranges::to<std::vector<const SceneNode*>>();
    }
}
