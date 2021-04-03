//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"

TEST(Texture, load_png)
{
    pkzo::Texture texture("../../pkzo-test/data/lena.png");
    EXPECT_EQ(glm::uvec2(512, 512), texture.get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.6f, 0.215686f, 0.301961f, 1.0f), texture.get_texel({265, 265}), 1e-6f);
}

TEST(Texture, load_jpg)
 {
    pkzo::Texture texture("../../pkzo-test/data/lena.jpg");
    EXPECT_EQ(glm::uvec2(512, 512), texture.get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.619608f, 0.223529f, 0.286275f, 1.0f), texture.get_texel({265, 265}), 1e-6f);
}

TEST(Texture, compare)
{
    auto lena_png = pkzo::Texture("../../pkzo-test/data/lena.png");
    auto lena_jpg = pkzo::Texture("../../pkzo-test/data/lena.jpg");

    EXPECT_FLOAT_EQ(0.0f, pkzo::compare(lena_png, lena_png));
    EXPECT_FLOAT_EQ(5033.1348f, pkzo::compare(lena_png, lena_jpg));
}

TEST(Texture, diff)
{
    auto lena_png = pkzo::Texture("../../pkzo-test/data/lena.png");
    auto rectangle = pkzo::Texture("../../pkzo-test/data/rectangle.png");
    auto ref = pkzo::Texture("../../pkzo-test/data/ref_diff.png");

    auto diff = pkzo::diff(lena_png, rectangle);

    auto diff_error = pkzo::compare(diff, ref);
    EXPECT_FLOAT_EQ(0.0f, diff_error);

    if (diff_error > 1e-4f)
    {
        diff.save("../../pkzo-test/data/test_diff.png");
    }
}