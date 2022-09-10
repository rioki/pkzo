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

#include "ScreenNode.h"

#include <memory>
#include <vector>

namespace ice
{
    class ICE_EXPORT ScreenNodeGroup : public ScreenNode
    {
    public:
        ScreenNodeGroup() noexcept = default;
        ScreenNodeGroup(const glm::mat3& transform) noexcept;

        void add_node(ScreenNode& node) noexcept;
        void add_node(const std::shared_ptr<ScreenNode>& node) noexcept;

        void remove_node(ScreenNode& node) noexcept;
        void remove_node(const std::shared_ptr<ScreenNode>& node) noexcept;

        std::vector<ScreenNode*> get_nodes() noexcept;
        std::vector<const ScreenNode*> get_nodes() const noexcept;


        void activate() override;
        void deactivate() override;

    private:
        std::vector<std::shared_ptr<ScreenNode>> nodes;
    };
}
