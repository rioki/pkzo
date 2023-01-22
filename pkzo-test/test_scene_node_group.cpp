// pkzo
// Copyright 2022-2023 Sean Farrell
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

TEST(SceneNodeGroup, default_contruct)
{
    auto node = pkzo::SceneNodeGroup{};
    EXPECT_GLM_NEAR(glm::mat4(1.0), node.get_transform(), 1e-4f);
}

TEST(SceneNodeGroup, init_transform)
{
    auto node = pkzo::SceneNodeGroup{glm::mat4(2.0f)};
    EXPECT_GLM_NEAR(glm::mat4(2.0), node.get_transform(), 1e-4f);
}

TEST(SceneNodeGroup, add_node)
{
    auto root = pkzo::SceneNodeGroup{};

    auto child = std::make_shared<pkzo::SceneNode>();
    root.add_node(child);

    auto nodes = root.get_nodes();
    ASSERT_EQ(1, nodes.size());
    EXPECT_EQ(child.get(), nodes[0]);

    EXPECT_EQ(&root, child->get_parent());
}

TEST(SceneNodeGroup, remove_child)
{
    pkzo::SceneNodeGroup root;

    auto child = std::make_shared<pkzo::SceneNode>();
    root.add_node(child);
    root.remove_node(child);

    auto nodes = root.get_nodes();
    ASSERT_EQ(0, nodes.size());

    EXPECT_EQ(nullptr, child->get_parent());
}

TEST(SceneNodeGroup, move_propagates_to_children)
{
    pkzo::SceneNodeGroup root;

    auto child = std::make_shared<pkzo::SceneNode>();
    root.add_node(child);

    auto count = 0u;
    child->on_move([&] () {
        count++;
    });

    root.set_transform(glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.2f, 0.3f)));

    EXPECT_EQ(1u, count);
}

TEST(SceneNodeGroup, add_and_remove_signals)
{
    auto root = pkzo::SceneNodeGroup{};

    auto count_add = 0u;
    root.on_add_node([&] () {
        count_add++;
    });

    auto count_remove = 0u;
    root.on_remove_node([&] () {
        count_remove++;
    });

    auto child = pkzo::SceneNode{};
    root.add_node(child);

    EXPECT_EQ(1u, count_add);
    EXPECT_EQ(0u, count_remove);

    root.remove_node(child);

    EXPECT_EQ(1u, count_add);
    EXPECT_EQ(1u, count_remove);
}

