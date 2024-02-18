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

#include <vector>
#include <memory>

#include <rex/managed_ptr.h>
#include <rex/ranges.h>

#include "defines.h"
#include "SceneNode.h"

namespace pkzo
{
    class PKZO_EXPORT Group : public SceneNode
    {
    public:
        Group();
        Group(glm::mat4 transform);
        Group(const Group& other);
        ~Group();

        std::string get_type() const noexcept override;
        std::unique_ptr<SceneNode> clone() const noexcept override;
        void serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const override;
        void deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir) override;

        void add_child(SceneNode& child);
        void add_child(std::unique_ptr<SceneNode> child);

        void remove_child(SceneNode& child);
        void remove_child(SceneNode* child);

        void activate() override;
        void deactivate() override;
        void update(float dt) override;

        std::vector<SceneNode*> get_children() noexcept;
        std::vector<const SceneNode*> get_children() const noexcept;

        template <typename Type>
        std::vector<Type*> find_descendants() noexcept;
        template <typename Type>
        std::vector<const Type*> find_descendants() const noexcept;

    private:
        std::vector<rex::managed_ptr<SceneNode>> children;
    };

    template <typename Type>
    std::vector<Type*> Group::find_descendants() noexcept
    {
        auto result = std::vector<Type*>{};

        for (auto& child : children)
        {
            if (auto typed_child = dynamic_cast<Type*>(child.get()))
            {
                result.push_back(typed_child);
            }

            if (auto group = dynamic_cast<Group*>(child.get()))
            {
                auto group_result = group->find_descendants<Type>();
                result.insert(result.end(), group_result.begin(), group_result.end());
            }
        }

        return result;
    }

    template <typename Type>
    std::vector<const Type*> Group::find_descendants() const noexcept
    {
        return const_cast<Group*>(this)->find_descendants<Type>()
               | rex::ranges::to<std::vector<const Type*>>();
    }
}
