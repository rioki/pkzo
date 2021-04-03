//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"

TEST(SceneNodeGroup, default_contruct)
{
    pkzo::three::SceneNodeGroup node;
    EXPECT_EQ(glm::mat4(1.0), node.get_transform());
}

TEST(SceneNodeGroup, init_transform)
{
    pkzo::three::SceneNodeGroup node(glm::mat4(2.0f));
    EXPECT_EQ(glm::mat4(2.0), node.get_transform());
}

TEST(SceneNodeGroup, add_child)
{
    pkzo::three::SceneNodeGroup root;

    auto child = std::make_shared<pkzo::three::SceneNode>();
    root.add_child(child);

    auto nodes = root.get_children();
    ASSERT_EQ(1, nodes.size());
    EXPECT_EQ(child, nodes[0]);

    EXPECT_EQ(&root, child->get_parent());
}

TEST(SceneNodeGroup, remove_child)
{
    pkzo::three::SceneNodeGroup root;

    auto child = std::make_shared<pkzo::three::SceneNode>();
    root.add_child(child);
    root.remove_child(child);

    auto nodes = root.get_children();
    ASSERT_EQ(0, nodes.size());

    EXPECT_EQ(nullptr, child->get_parent());
}
