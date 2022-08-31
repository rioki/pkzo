// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/glm_2d.h>
#include <ice/Screen.h>

#include "glm_checks.h"

TEST(Screen, init)
{
    auto screen = ice::Screen(glm::vec2(640.0f, 480.0f));
    EXPECT_GLM_NEAR(glm::mat3(1.0), screen.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(640.0f, 480.0f), screen.get_size(), 1e-4f);
}