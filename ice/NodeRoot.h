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

#include "NodeGroup.h"

namespace ice
{
    class Engine;

    template <typename Type>
    class NodeRoot : public NodeGroup<Type>
    {
    public:
        NodeRoot() = default;

        ~NodeRoot()
        {
            assert(active == false);
        }

        void activate(Engine& engine)
        {
            assert(false == active);
            active = true;

            local_activate(engine);
            NodeGroup<Type>::activate();
        }

        void deactivate(Engine& engine)
        {
            assert(true == active);
            NodeGroup<Type>::deactivate();

            local_deactivate(engine);

            active = false;
        }

        bool is_active() const noexcept
        {
            return active;
        }

    protected:
        virtual void local_activate(Engine& engine) = 0;
        virtual void local_deactivate(Engine& engine) = 0;

    private:
        bool active = false;
    };
}
