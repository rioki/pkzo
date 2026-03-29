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

#include <memory>
#include <vector>

#include "stdng.h"
#include "debug.h"
#include "Node.h"

namespace pkzo
{
    template <typename Type>
    class Group : public Node<Type>
    {
    public:

        using NodeT  = Node<Type>;
        using Init   = Node<Type>::Init;
        using Bounds = Node<Type>::Bounds;

        Group(Init init = {}) noexcept
        : Node<Type>(std::move(init)) {}

        template <typename T>
        T* add(T::Init init = {})
        {
            init.parent = this;

            auto child = std::make_unique<T>(std::move(init));
            auto ptr = child.get();
            children.push_back(std::move(child));

            if (Node<Type>::is_active())
            {
                ptr->activate();
            }

            return ptr;
        }

        void remove(NodeT* child)
        {
            auto i = std::ranges::find_if(children, [&] (auto& n) {
                return n.get() == child;
            });
            check(i != children.end());

            if (Node<Type>::is_active())
            {
                child->deactivate();
            }

            children.erase(i);
        }

        void remove_all_children()
        {
            if (Node<Type>::is_active())
            {
                deactivate();
            }
            children.clear();
        }

        std::vector<NodeT*> get_children()
        {
            auto result = std::vector<NodeT*>{};

            for (const auto& ptr : children)
            {
                result.push_back(ptr.get());
            }

            return result;
        }

        std::vector<const NodeT*> get_children() const
        {
            auto result = std::vector<const NodeT*>{};

            for (const auto& ptr : children)
            {
                result.push_back(ptr.get());
            }

            return result;
        }

        template <typename T>
        std::vector<T*> find_decendents()
        {
            auto result = std::vector<T*>{};
            find_decendent_impl<T>(result);
            return result;
        }

        template <typename T>
        std::vector<const T*> find_decendents() const
        {
            auto result = std::vector<const T*>{};
            find_decendent_impl<const T>(result);
            return result;
        }

        void activate() override
        {
            Node<Type>::activate();
            for (const auto& child : children)
            {
                child->activate();
            }
        }

        void deactivate() override
        {
            for (const auto& child : children)
            {
                child->deactivate();
            }
            Node<Type>::deactivate();
        }

        void update(float dt) override
        {
            for (const auto& child : children)
            {
                child->update(dt);
            }
        }

        Bounds get_bounds() const override
        {
            Bounds bounds;
            for (const auto& child : children)
            {
                bounds = merge(bounds, transform(child->get_transform(), child->get_bounds()));
            }
            return bounds;
        }

    private:
        std::vector<std::unique_ptr<NodeT>> children;

        template <typename T>
        void find_decendent_impl(std::vector<T*>& result)
        {
            for (const auto& child : children)
            {
                auto c = dynamic_cast<T*>(child.get());
                if (c)
                {
                    result.push_back(c);
                }
                auto g = dynamic_cast<Group*>(child.get());
                if (g)
                {
                    g->find_decendent_impl(result);
                }
            }
        }
    };
}
