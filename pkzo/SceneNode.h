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

#pragma once

#include <memory>
#include <functional>
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include "defines.h"

namespace pkzo
{
    class Scene;

    class PKZO_EXPORT SceneNode
    {
    public:
        using TypeFactory = std::function<std::unique_ptr<SceneNode> ()>;

        static std::unique_ptr<SceneNode> create(const std::string& type);
        static void register_type(const std::string& type, const TypeFactory& factory);

        SceneNode();
        SceneNode(glm::mat4 transform);
        SceneNode(const SceneNode& other);
        virtual ~SceneNode();

        virtual std::string get_type() const noexcept = 0;
        virtual std::unique_ptr<SceneNode> clone() const noexcept = 0;
        virtual void serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const;
        virtual void deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir);

        SceneNode* get_parent() noexcept;
        const SceneNode* get_parent() const noexcept;

        template <typename Type>
        Type* find_ancestor() noexcept;
        template <typename Type>
        const Type* find_ancestor() const noexcept;

        Scene* get_scene() noexcept;
        const Scene* get_scene() const noexcept;

        virtual bool is_active() const noexcept;
        virtual void activate();
        virtual void deactivate();

        virtual void update(float dt);

        void set_transform(glm::mat4 value) noexcept;
        glm::mat4 get_transform() const noexcept;
        glm::mat4 get_global_transform() const noexcept;

    private:
        SceneNode* parent    = nullptr;
        glm::mat4  transform = glm::mat4(1.0f);

        SceneNode& operator = (SceneNode& other) = delete;

        friend class Group;
    };

    template <typename Type>
    Type* SceneNode::find_ancestor() noexcept
    {
        if (parent == nullptr)
        {
            return nullptr;
        }

        auto result = dynamic_cast<Type*>(parent);
        if (result != nullptr)
        {
            return result;
        }
        else
        {
            return parent->find_ancestor<Type>();
        }
    }

    template <typename Type>
    const Type* SceneNode::find_ancestor() const noexcept
    {
        return const_cast<SceneNode*>(this)->find_ancestor<Type>();
    }

    template <typename Type>
    struct TypeRegistration
    {
        TypeRegistration(const std::string& type)
        {
            SceneNode::register_type(type, []() {
                return std::make_unique<Type>();
            });
        }
    };
}

#define PKZO_THREE_REGISTER_TYPE(Type) pkzo::TypeRegistration<Type> Type##Registration(#Type);
