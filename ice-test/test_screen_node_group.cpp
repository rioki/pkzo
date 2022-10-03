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

TEST(ScreenNodeGroup, default_contruct)
{
    auto node = ice::ScreenNodeGroup{};
    EXPECT_GLM_NEAR(glm::mat3(1.0), node.get_transform(), 1e-4f);
}

TEST(ScreenNodeGroup, init_transform)
{
    auto node = ice::ScreenNodeGroup{glm::mat3(2.0f)};
    EXPECT_GLM_NEAR(glm::mat3(2.0), node.get_transform(), 1e-4f);
}

TEST(ScreenNodeGroup, add_node)
{
    auto root = ice::ScreenNodeGroup{};

    auto child = std::make_shared<ice::ScreenNode>();
    root.add_node(child);

    auto nodes = root.get_nodes();
    ASSERT_EQ(1, nodes.size());
    EXPECT_EQ(child.get(), nodes[0]);

    EXPECT_EQ(&root, child->get_parent());
}

TEST(ScreenNodeGroup, remove_child)
{
    ice::ScreenNodeGroup root;

    auto child = std::make_shared<ice::ScreenNode>();
    root.add_node(child);
    root.remove_node(child);

    auto nodes = root.get_nodes();
    ASSERT_EQ(0, nodes.size());

    EXPECT_EQ(nullptr, child->get_parent());
}

TEST(ScreenNodeGroup, move_propagates_to_children)
{
    ice::ScreenNodeGroup root;

    auto child = std::make_shared<ice::ScreenNode>();
    root.add_node(child);

    auto count = 0u;
    child->on_move([&] () {
        count++;
    });

    root.set_transform(glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.2f, 0.3f)));

    EXPECT_EQ(1u, count);

}
