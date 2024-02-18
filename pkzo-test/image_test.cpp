// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "pch.h"

#include <pkzo/Image.h>

TEST(Texture, load_png)
{
    auto test_input = testing::get_test_input();
    auto texture = pkzo::Image(testing::get_test_input() / "textures/AngryCat.png");

    EXPECT_EQ(texture.get_size(), glm::uvec2(512, 512));
    EXPECT_EQ(texture.get_color_mode(), pkzo::ColorMode::BGRA);
}

TEST(Texture, load_jpg)
{
    auto texture = pkzo::Image(testing::get_test_input() / "textures/AngryCat.jpg");

    EXPECT_EQ(texture.get_size(), glm::uvec2(512, 512));
    EXPECT_EQ(texture.get_color_mode(), pkzo::ColorMode::BGR);
}

TEST(Texture, diff)
{
    auto cat       = pkzo::Image(testing::get_test_input() / "textures/AngryCat.png");
    auto rectangle = pkzo::Image(testing::get_test_input() / "textures/rectangle.png");

    auto diff = pkzo::diff(cat, rectangle);
    auto ref  = pkzo::Image(testing::get_test_input() / "references/Texture-diff-ref.png");

    EXPECT_EQ(pkzo::compare(diff, ref), 0.0f);

    EXPECT_IMAGE_REF_EQ(diff); // again, but with test magic
}
