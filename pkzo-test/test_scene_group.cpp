// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include <pkzo-three/SceneGroup.h>

#include <gtest/gtest.h>

TEST(SceneGroup, add_node_shared_ptr)
{
    auto node = std::make_shared<pkzo::three::SceneNode>();
    pkzo::three::SceneGroup group;

    group.add_node(node);

    auto nodes = group.get_nodes();
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0], node);
    EXPECT_EQ(node->get_parent(), &group);
}

TEST(SceneGroup, add_node_reference)
{
    pkzo::three::SceneNode node;
    pkzo::three::SceneGroup group;

    group.add_node(node);

    auto nodes = group.get_nodes();
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0].get(), &node);
    EXPECT_EQ(node.get_parent(), &group);
}

TEST(SceneGroup, parent_out_of_scope_before_child)
{
    pkzo::three::SceneNode child;
    {
        pkzo::three::SceneGroup parent;
        parent.add_node(child);
    }

    EXPECT_EQ(child.get_parent(), nullptr);
}

TEST(SceneGroup, remove_node_shared_ptr)
{
    auto node = std::make_shared<pkzo::three::SceneNode>();
    pkzo::three::SceneGroup group;
    group.add_node(node);

    group.remove_node(node);

    auto nodes = group.get_nodes();
    EXPECT_TRUE(nodes.empty());
    EXPECT_EQ(node->get_parent(), nullptr);
}

TEST(SceneGroup, remove_node_reference)
{
    pkzo::three::SceneNode node;
    pkzo::three::SceneGroup group;
    group.add_node(node);

    group.remove_node(node);

    auto nodes = group.get_nodes();
    EXPECT_TRUE(nodes.empty());
    EXPECT_EQ(node.get_parent(), nullptr);
}
