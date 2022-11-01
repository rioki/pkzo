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
    auto text_color         = ice::rgba(0x000000ff);
    auto font               = std::shared_ptr<ice::Font>(); // TODO prelaoded and cached  test font
    auto background_color   = ice::rgba(0x349eebff);
    auto background_texture = std::shared_ptr<ice::Texture>(); // TODO preloaded and cached test image

    auto button = ice::ui::Button(position, size, "Label", font, text_color, background_texture, background_color);

    EXPECT_GLM_NEAR(position,       button.get_position(), 1e-4f);
    EXPECT_GLM_EQ(size,             button.get_size());
    EXPECT_EQ("Label",              button.get_label_text());
    EXPECT_EQ(font,                 button.get_label_font());
    EXPECT_GLM_EQ(text_color,       button.get_label_color());
    EXPECT_EQ(background_texture,   button.get_background_texture());
    EXPECT_GLM_EQ(background_color, button.get_background_color());

}