// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Font.h>

#include "test_env.h"
#include "glm_checks.h"
#include "texture_checks.h"

TEST(Font, load_ttf)
{
    auto font = std::make_shared<ice::Font>(ice::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 32);

    auto estimate = font->estimate("pzko");
    EXPECT_EQ(glm::uvec2(77u, 35u), estimate);

    auto texture  = font->render("pzko");
    EXPECT_EQ(estimate, texture->get_size());
    EXPECT_TEXTURE_REF_EQ(texture);
}
