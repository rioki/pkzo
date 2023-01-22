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

TEST(Label, default_contruct)
{
    auto label = pkzo::Label();
    EXPECT_GLM_NEAR(glm::vec2(0.0f), label.get_position(), 1e-4f);
}

TEST(Label, init)
{
    auto position = glm::vec2(42.0f);
    auto color    = pkzo::rgba(0x000000ff);
    auto font     = std::make_shared<pkzo::Font>(pkzo::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 16);

    auto label = pkzo::Label(position, "Label", font, color);

    EXPECT_GLM_NEAR(position,                           label.get_position(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(font->estimate("Label")), label.get_size(), 1e-4f);
    EXPECT_EQ("Label",                                  label.get_caption());
    EXPECT_EQ(font,                                     label.get_font());
    EXPECT_GLM_EQ(color,                                label.get_color());
}

TEST(Label, cant_be_smaller_than_text)
{
    auto color    = pkzo::rgba(0x000000ff);
    auto font     = std::make_shared<pkzo::Font>(pkzo::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 16);

    auto label = pkzo::Label("Label", font, color);

    auto min_size = glm::vec2(font->estimate("Label"));

    EXPECT_GLM_NEAR(min_size, label.get_size(), 1e-4f);
    EXPECT_GLM_NEAR(min_size, label.get_min_size(), 1e-4f);

    // larger
    label.set_size(glm::vec2(150.0f, 250.0f));
    EXPECT_GLM_NEAR(glm::vec2(150.0f, 250.0f), label.get_size(), 1e-4f);

    // smaller
    label.set_size(glm::vec2(2.0f, 3.0f));
    EXPECT_GLM_NEAR(min_size, label.get_size(), 1e-4f);
}
