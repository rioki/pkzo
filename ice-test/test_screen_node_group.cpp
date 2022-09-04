// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

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