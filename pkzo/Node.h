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

#include "glm_2d.h"

namespace pkzo
{
    template <typename Type>
    struct NodeTraits {};

    template <typename Type>
    class Node
    {
    public:
        using NodeT  = Node<Type>;
        using Matrix = NodeTraits<Type>::Matrix;

        struct Init
        {
            NodeT* parent    = nullptr;
            Matrix transform = Matrix(1.0f);
        };

        Node(Init init = {})
        : parent(init.parent), transform(init.transform)
        {
            if (parent != nullptr)
            {
                parent_move_slot = parent->on_move([this] () {
                    move_signal.emit();
                });
            }
        }

        virtual ~Node() = default;

        [[nodiscard]]
        NodeT* get_parent()
        {
            return parent;
        }

        [[nodiscard]]
        const NodeT* get_parent() const
        {
            return parent;
        }

        [[nodiscard]]
        Type* get_root()
        {
            auto self = dynamic_cast<Type*>(this);
            if (self != nullptr)
            {
                return self;
            }
            return find_ancestor<Type>();
        }

        [[nodiscard]]
        const Type* get_root() const
        {
            return const_cast<Node<Type>*>(this)->get_root();
        }

        template <typename T>
        [[nodiscard]]
        T* find_ancestor()
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
        [[nodiscard]]
        const T* find_ancestor() const
        {
            return const_cast<Node<Type>*>(this)->find_ancestor<T>();
        }

        [[nodiscard]]
        const Matrix& get_transform() const
        {
            return transform;
        }

        [[nodiscard]]
        Matrix get_world_transform() const
        {
            if (parent)
            {
                return parent->get_world_transform() * transform;
            }
            else
            {
                return transform;
            }
        }

        [[nodiscard]]
        void set_transform(const Matrix& value)
        {
            transform = value;
            move_signal.emit();
        }

        rsig::connection on_move(const std::function<void ()>& handler)
        {
            return move_signal.connect(handler);
        }

        bool is_active() const
        {
            return active;
        }

        virtual void activate()
        {
            active = true;
        }

        virtual void deactivate()
        {
            active = false;
        }

        virtual void update(float dt) {}

    private:
        Node<Type>*    parent    = nullptr;
        Matrix         transform = Matrix(1.0f);
        bool           active    = false;
        rsig::signal<> move_signal;
        rsig::slot     parent_move_slot;

        Node(const Node<Type>&) = delete;
        Node<Type>& operator = (const Node<Type>&) = delete;
    };

    constexpr glm::mat4 position(const glm::vec3& value)
    {
        return glm::translate(glm::mat4(1.0f), value);
    }

    constexpr glm::mat4 position(float x, float y, float z)
    {
        return position(glm::vec3(x, y, z));
    }
}

