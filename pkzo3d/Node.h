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

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <rsig/rsig.h>

#include <pkzo/Bounds.h>

#include "api.h"

namespace pkzo3d
{
    class Scene;

    using pkzo::Bounds;

    class PKZO3D_EXPORT Node
    {
    public:
        struct Specs
        {
            Node*     parent    = nullptr;
            glm::mat4 transform = glm::mat4(1.0f);
        };

        Node(Specs specs);

        virtual ~Node();

        Scene* get_scene();
        const Scene* get_scene() const;

        Node* get_parent();
        const Node* get_parent() const;

        template <typename T>
        T* find_ancestor();
        template <typename T>
        const T* find_ancestor() const;

        void set_transform(const glm::mat4& value);
        const glm::mat4& get_transform() const;
        glm::mat4 get_global_transform() const;

        virtual Bounds get_bounds() const;

        rsig::connection on_move(const std::function<void ()>& handler);

        virtual void update(float dt);

    private:
        Node*     parent;
        glm::mat4 transform;

        rsig::signal<> move_signal;
        rsig::slot     parent_move_slot;

        Node(const Node&) = delete;
        Node& operator = (const Node&) = delete;
    };

    template <typename T>
    T* Node::find_ancestor()
    {
        auto p = dynamic_cast<T*>(parent);
        if (nullptr != p)
        {
            return p;
        }
        if (parent != nullptr)
        {
            return parent->find_ancestor<T>();
        }
        return nullptr;
    }

    template <typename T>
    const T* Node::find_ancestor() const
    {
        return const_cast<Node*>(this)->find_ancestor<T>();
    }

    constexpr glm::mat4 position(const glm::vec3& value)
    {
        return glm::translate(glm::mat4(1.0f), value);
    }

    constexpr glm::mat4 position(float x, float y, float z)
    {
        return position(glm::vec3(x, y, z));
    }

    inline glm::mat4 lookat(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return glm::inverse(glm::lookAt(position, target, up));
    }
}
