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

TEST(HorizontalLayout, default_size)
{
    auto layout = ice::ui::HorizontalLayout{};

    EXPECT_GLM_EQ(glm::vec2(0.0f), layout.get_size());
}

TEST(HorizontalLayout, add_size)
{
    auto lib   = ice::AssetLibrary{};
    auto theme = std::make_shared<ice::ui::Style>(lib, ice::test::get_asset_folder() / "ui/LightBlue.json");

    auto margin = 2.0f;
    auto layout = ice::ui::HorizontalLayout{margin};

    auto button = ice::ui::Button(theme, "A Button");
    layout.add_node(button);

    auto label = ice::ui::Label(theme, "A Label");
    layout.add_node(label);

    auto expected = glm::vec2(button.get_size().x + label.get_size().x + margin, std::max(button.get_size().y, label.get_size().y));
    EXPECT_EQ(expected, layout.get_size());
}

TEST(HorizontalLayout, size_single_item)
{
    auto lib   = ice::AssetLibrary{};
    auto theme = std::make_shared<ice::ui::Style>(lib, ice::test::get_asset_folder() / "ui/LightBlue.json");

    auto margin = 2.0f;
    auto layout = ice::ui::HorizontalLayout{margin};

    auto button = ice::ui::Button(theme, "A Button");
    layout.add_node(button);

    EXPECT_EQ(button.get_size(), layout.get_size());
}

TEST(VerticalLayout, default_size)
{
    auto layout = ice::ui::VerticalLayout{};

    EXPECT_GLM_EQ(glm::vec2(0.0f), layout.get_size());
}

TEST(VerticalLayout, add_size)
{
    auto lib   = ice::AssetLibrary{};
    auto theme = std::make_shared<ice::ui::Style>(lib, ice::test::get_asset_folder() / "ui/LightBlue.json");

    auto margin = 2.0f;
    auto layout = ice::ui::VerticalLayout{margin};

    auto button = ice::ui::Button(theme, "A Button");
    layout.add_node(button);

    auto label = ice::ui::Label(theme, "A Label");
    layout.add_node(label);

    auto expected = glm::vec2(std::max(button.get_size().x, label.get_size().x), button.get_size().y + label.get_size().y + margin);
    EXPECT_EQ(expected, layout.get_size());
}

TEST(VerticalLayout, size_single_item)
{
    auto lib   = ice::AssetLibrary{};
    auto theme = std::make_shared<ice::ui::Style>(lib, ice::test::get_asset_folder() / "ui/LightBlue.json");

    auto margin = 2.0f;
    auto layout = ice::ui::VerticalLayout{margin};

    auto button = ice::ui::Button(theme, "A Button");
    layout.add_node(button);

    EXPECT_EQ(button.get_size(), layout.get_size());
}
