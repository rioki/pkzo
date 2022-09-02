// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/glm_2d.h>
#include <ice/ScreenNode.h>
#include <ice/ScreenNodeGroup.h>

#include "glm_checks.h"

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
