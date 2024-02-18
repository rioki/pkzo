// pkzo
// Copyright 2010-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "defines.h"

namespace pkzo
{
    template <typename Type>
    struct NodeTraits {};

    template <typename Type>
    class Node
    {
    public:
        using Matrix = NodeTraits<Type>::Matrix;
        using Bounds = NodeTraits<Type>::Bounds;

        Node() noexcept = default;

        explicit Node(const Matrix& _transform) noexcept
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
            if (auto this_root = dynamic_cast<Type*>(this))
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
            if (auto p = dynamic_cast<T*>(parent))
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

        rex::connection on_move(const std::function<void ()>& cb) noexcept
        {
            return move_signal.connect(cb);
        }

        rex::signal<>& get_move_signal() noexcept
        {
            return move_signal;
        }

        virtual Bounds get_bounds() const noexcept
        {
            return {};
        }

        virtual void activate()
        {
            active = true;
        }

        virtual void deactivate()
        {
            active = false;
        }

        bool is_active() const noexcept
        {
            return active;
        }

        virtual void update(std::chrono::milliseconds dt) {}

    private:
        bool           active    = false;
        Node<Type>*    parent    = nullptr;
        Matrix         transform = Matrix(1.0f);
        rex::signal<> move_signal;

        Node<Type>(const Node<Type>&) = delete;
        Node<Type>& operator = (const Node<Type>&) = delete;

        template<class T> friend class NodeGroup;
    };
}