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

TEST(Label, default_contruct)
{
    auto label = ice::ui::Label();
    EXPECT_GLM_NEAR(glm::mat3(1.0), label.get_transform(), 1e-4f);
}

TEST(Label, init)
{
    auto position = glm::mat3(1.0f);
    auto color    = ice::rgba(0x000000ff);
    auto font     = std::shared_ptr<ice::Font>(); // TODO prelaoded and cached  test font

    auto label = ice::ui::Label(position, "Label", font, color);

    EXPECT_GLM_NEAR(position, label.get_transform(), 1e-4f);
    EXPECT_EQ("Label",        label.get_text());
    EXPECT_EQ(font,           label.get_font());
    EXPECT_GLM_EQ(color,      label.get_color());

}