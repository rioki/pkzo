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

TEST(Button, default_contruct)
{
    auto button = ice::ui::Button();
    EXPECT_GLM_NEAR(glm::vec2(0.0f), button.get_position(), 1e-4f);
}

TEST(Button, init)
{
    auto position           = glm::vec2(42.0f);
    auto size               = glm::vec2(150, 36);
    auto color              = ice::rgba(0x000000ff);
    auto font               = std::make_shared<ice::Font>(ice::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 16);
    auto background_color   = ice::rgba(0x349eebff);
    auto background_texture = std::make_shared<ice::Texture>(ice::test::get_test_input() / "AngryCat.jpg");

    auto button = ice::ui::Button(position, size, "Label", font, color, background_color, background_texture);

    EXPECT_GLM_NEAR(position,       button.get_position(), 1e-4f);
    EXPECT_GLM_EQ(size,             button.get_size());
    EXPECT_EQ("Label",              button.get_caption());
    EXPECT_EQ(font,                 button.get_font());
    EXPECT_GLM_EQ(color,            button.get_color());
    EXPECT_GLM_EQ(background_color, button.get_background_color());
    EXPECT_EQ(background_texture,   button.get_background_texture());

}

TEST(Button, init_from_style)
{
    auto position           = glm::vec2(42.0f);
    auto size               = glm::vec2(150, 36);
    auto color              = ice::rgba(0x000000ff);
    auto font               = std::make_shared<ice::Font>(ice::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 16);
    auto background_color   = ice::rgba(0x349eebff);
    auto background_texture = std::make_shared<ice::Texture>(ice::test::get_test_input() / "AngryCat.jpg");

    auto style = std::make_shared<ice::ui::Style>(ice::test::get_test_input());
    style->set_vec2("Button", "size", size);
    style->set_font("Button", "font", font);
    style->set_color("Button", "color", color);
    style->set_color("Button", "background_color", background_color);
    style->set_texture("Button", "background_texture", background_texture);

    auto button = ice::ui::Button(position, style, "Label");

    EXPECT_GLM_NEAR(position,       button.get_position(), 1e-4f);
    EXPECT_GLM_EQ(size,             button.get_size());
    EXPECT_EQ("Label",              button.get_caption());
    EXPECT_EQ(font,                 button.get_font());
    EXPECT_GLM_EQ(color,            button.get_color());
    EXPECT_GLM_EQ(background_color, button.get_background_color());
    EXPECT_EQ(background_texture,   button.get_background_texture());
}