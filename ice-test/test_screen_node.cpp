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

#include "pch.h"

#include <ice/ice.h>

TEST(ScreenNode, default_contruct)
{
    auto node = ice::ScreenNode{};
    EXPECT_GLM_NEAR(glm::mat3(1.0), node.get_transform(), 1e-4f);
}

TEST(ScreenNode, init_transform)
{
    auto node = ice::ScreenNode{glm::mat3(2.0f)};
    EXPECT_GLM_NEAR(glm::mat3(2.0), node.get_transform(), 1e-4f);
}

TEST(ScreenNode, world_transform)
{
    auto root_transform = glm::mat3(1.0f);
    root_transform = glm::translate(root_transform, {1.0f, 0.0f});
    root_transform = glm::rotate(root_transform, glm::radians(45.0f));
    auto root = ice::ScreenNodeGroup(root_transform);

    auto child_transform = glm::mat3(1.0f);
    child_transform = glm::translate(child_transform, {0.0f, 1.0f});
    child_transform = glm::rotate(child_transform, glm::radians(30.0f));
    auto child = std::make_shared<ice::ScreenNode>(child_transform);
    root.add_node(child);

    EXPECT_GLM_NEAR(root_transform, root.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(root_transform, root.get_world_transform(), 1e-4f);
    EXPECT_GLM_NEAR(child_transform, child->get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(root_transform * child_transform, child->get_world_transform(), 1e-4f);
}
