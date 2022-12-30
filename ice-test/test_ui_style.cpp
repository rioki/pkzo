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

using ice::test::get_test_input;

TEST(Style, load_empty_theme)
{
    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());

    EXPECT_NO_THROW(ice::ui::Style(lib, get_test_input() / "EmptyTheme.json"));
}

TEST(Style, invlaud_file_throws)
{
    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());

    EXPECT_THROW(ice::ui::Style(lib, get_test_input() / "InvalidFile.json"), std::runtime_error);
}

TEST(Style, get_color)
{
    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");
    // on Button
    EXPECT_EQ(glm::vec4(0.369, 0.357, 0.353, 0.5), theme.get_color("Button", "background_color"));
    // on default
    EXPECT_EQ(glm::vec4(0.369, 0.357, 0.353, 1.0), theme.get_color("Button", "text_color"));
}

TEST(Style, get_font)
{
    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");
    // on Title
    auto a = theme.get_font("Title", "title_font");
    EXPECT_EQ("DejaVuSansMono.ttf", a->get_file().filename());
    EXPECT_EQ(32, a->get_size());
    // on default
    auto b = theme.get_font("Title", "font");
    EXPECT_EQ("DejaVuSans.ttf", b->get_file().filename());
    EXPECT_EQ(24, b->get_size());
}

TEST(Style, get_texture)
{
    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");
    // on Title as string
    auto a = theme.get_texture("Title", "title_background");
    EXPECT_EQ("AngryCat.png", a->get_file().filename());
    // on Title as object
    auto b = theme.get_texture("Title", "title_forefround");
    EXPECT_EQ("AngryCat.jpg", b->get_file().filename());
    // on default as string
    auto c = theme.get_texture("Title", "background");
    EXPECT_EQ("rectangle.png", c->get_file().filename());
    // on default as object
    auto d = theme.get_texture("Title", "forefround");
    EXPECT_EQ("Texture-diff-ref.png", d->get_file().filename());
}

TEST(Style, get_null_texture)
{
    auto lib = ice::AssetLibrary{};

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");

    auto a = theme.get_texture("None", "background_texture");
    EXPECT_EQ(nullptr, a);
}

TEST(Style, get_null_font)
{
    auto lib = ice::AssetLibrary{};

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");

    auto a = theme.get_font("None", "font");
    EXPECT_EQ(nullptr, a);
}

TEST(Style, get_null_color)
{
    auto lib = ice::AssetLibrary{};

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");

    auto a = theme.get_color("None", "color");
    EXPECT_GLM_EQ(glm::vec4(0.0f), a);
}

TEST(Style, get_variant)
{
    auto lib = ice::AssetLibrary{};

    auto theme = ice::ui::Style(lib, get_test_input() / "TestTheme.json");

    EXPECT_EQ(121, theme.get_int("BaseType/Variant", "value1"));
    EXPECT_EQ(24, theme.get_int("BaseType/Variant", "value2"));
}