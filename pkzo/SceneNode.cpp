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
#include "SceneNode.h"

#include "Scene.h"

namespace pkzo
{
    auto& get_factories()
    {
        static std::map<std::string, SceneNode::TypeFactory, std::less<>> factories;
        return factories;
    }

    std::unique_ptr<SceneNode> SceneNode::create(const std::string& type)
    {
        auto& factories = get_factories();

        auto factory = factories.find(type);
        if (factory == factories.end())
        {
             throw std::runtime_error(tfm::format("Unknwon scene node type: %s", type));
        }

        return factory->second();
    }

    void SceneNode::register_type(const std::string& type, const TypeFactory& factory)
    {
        auto& factories = get_factories();

        check(factory != nullptr);
        check(factories.find(type) == factories.end());
        factories[type] = factory;
    }

    SceneNode::SceneNode() = default;

    SceneNode::SceneNode(glm::mat4 t)
    : transform(t) {}

    SceneNode::SceneNode(const SceneNode& other)
    : transform(other.transform) {}

    SceneNode::~SceneNode() = default;

    void SceneNode::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        j["type"]      = get_type();
        j["transform"] = transform;
    }

    void SceneNode::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        transform = j.value("transform", transform);
    }

    SceneNode* SceneNode::get_parent() noexcept
    {
        return parent;
    }

    const SceneNode* SceneNode::get_parent() const noexcept
    {
        return parent;
    }

    Scene* SceneNode::get_scene() noexcept
    {
        auto scene = dynamic_cast<Scene*>(this);
        if (scene != nullptr)
        {
            return scene;
        }

        if (parent != nullptr)
        {
            return find_ancestor<Scene>();
        }
        else
        {
            return nullptr;
        }
    }

    const Scene* SceneNode::get_scene() const noexcept
    {
        return const_cast<SceneNode*>(this)->get_scene();
    }

    bool SceneNode::is_active() const noexcept
    {
        auto scene = get_scene();
        if (scene != nullptr)
        {
            return scene->is_active();
        }
        else
        {
            return false;
        }
    }

    void SceneNode::activate() {}

    void SceneNode::deactivate() {}

    void SceneNode::update(float dt) {}

    void SceneNode::set_transform(glm::mat4 value) noexcept
    {
        transform = value;
    }

    glm::mat4 SceneNode::get_transform() const noexcept
    {
        return transform;
    }

    glm::mat4 SceneNode::get_global_transform() const noexcept
    {
        if (parent != nullptr)
        {
            return parent->get_global_transform() * transform;
        }
        else
        {
            return transform;
        }
    }
}

