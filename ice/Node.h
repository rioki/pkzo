// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "config.h"

#include <rsig/rsig.h>

namespace ice
{
    template <typename Type>
    struct NodeTraits {};

    template <typename Type>
    class Node
    {
    public:
        using Matrix = NodeTraits<Type>::Matrix;

        Node() noexcept = default;

        Node(const Matrix& _transform) noexcept
        : transform(_transform) {}

        virtual ~Node() = default;

        Node<Type>* get_parent() noexcept
        {
            return parent;
        }

        const Node<Type>* get_parent() const noexcept
        {
            return parent;
        }

        Type* get_root() noexcept
        {
            auto this_root = dynamic_cast<Type*>(this);
            if (this_root)
            {
                return this_root;
            }

            return find_ancestor<Type>();
        }

        const Type* get_root() const noexcept
        {
            return const_cast<Node<Type>*>(this)->get_root();
        }

        template <typename T>
        T* find_ancestor() noexcept
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
        const T* find_ancestor() const noexcept
        {
            return const_cast<Node<Type>*>(this)->find_ancestor();
        }

        void set_transform(const Matrix& value) noexcept
        {
            transform = value;
            move_signal.emit();
        }

        const Matrix& get_transform() const noexcept
        {
            return transform;
        }

        Matrix get_world_transform() const noexcept
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

        rsig::connection on_move(const std::function<void ()>& cb) noexcept
        {
            return move_signal.connect(cb);
        }

        rsig::signal<>& get_move_signal() noexcept
        {
            return move_signal;
        }

        virtual void activate() {}

        virtual void deactivate() {}

    private:
        Node<Type>* parent    = nullptr;
        Matrix              transform = Matrix(1.0f);
        rsig::signal<>      move_signal;

        Node<Type>(const Node<Type>&) = delete;
        Node<Type>& operator = (const Node<Type>&) = delete;

        template<class T> friend class NodeGroup;
    };
}
