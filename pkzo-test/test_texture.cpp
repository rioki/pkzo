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


#include <pkzo/Texture.h>

#include <gtest/gtest.h>

#include <pkzo/utils.h>

#include "glm_gtest.h"
#include "pkzo_test.h"

using pkzo::test::get_test_input;

TEST(Texture, load_png)
{
    auto texture = pkzo::Texture::load(get_test_input() / "AngryCat.png");
    EXPECT_EQ(glm::uvec2(512, 512), texture->get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.38823530077934265f, 0.31764706969261169f, 0.30588236451148987f, 1.0f), texture->get_texel({265, 265}), 1e-6f);
}

TEST(Texture, load_jpg)
 {
    auto texture = pkzo::Texture::load(get_test_input() / "AngryCat.jpg");
    EXPECT_EQ(glm::uvec2(512, 512), texture->get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.3960784375667572f, 0.32941177487373352f, 0.30196079611778259f, 1.0f), texture->get_texel({265, 265}), 1e-6f);
}

TEST(Texture, load_jpg_from_memory)
 {
    auto buffer = pkzo::load_binary_file(get_test_input() / "AngryCat.jpg");
    auto texture = pkzo::Texture::load_memory(pkzo::Format::JPEG, buffer.data(), buffer.size());
    EXPECT_EQ(glm::uvec2(512, 512), texture->get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.3960784375667572f, 0.32941177487373352f, 0.30196079611778259f, 1.0f), texture->get_texel({265, 265}), 1e-6f);
}

TEST(Texture, load_hdr)
{
    auto texture = pkzo::Texture::load(get_test_input() / "chinese_garden_1k.hdr");
    EXPECT_EQ(pkzo::DataType::FLOAT, texture->get_data_type());
    EXPECT_EQ(glm::uvec2(1024, 512), texture->get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.115234375f, 0.1279296875f, 0.0185546875f, 1.0f), texture->get_texel({265, 265}), 1e-6f);
}

TEST(Texture, from_memory)
{
    auto buffer = std::vector<uint8_t>{
        0xFF, 0x00, 0x00, 0xFF,
        0x00, 0xFF, 0x00, 0xFF,
        0x00, 0x00, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0xFF
    };

    auto texture = pkzo::Texture::create_from_buffer({2,2}, pkzo::ColorMode::BGRA, pkzo::DataType::UINT8, buffer.data(), "test image");
    EXPECT_EQ(glm::uvec2(2, 2), texture->get_size());
    EXPECT_GLM_NEAR(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture->get_texel({0, 0}), 1e-6f);
}

TEST(Texture, compare)
{
    auto png = pkzo::Texture::load(get_test_input() / "AngryCat.png");
    auto jpg = pkzo::Texture::load(get_test_input() / "AngryCat.jpg");

    EXPECT_FLOAT_EQ(0.0f, pkzo::compare(png, png));
    EXPECT_FLOAT_EQ(1787.4628f, pkzo::compare(png, jpg));
}

TEST(Texture, diff)
{
    auto angry_cat  = pkzo::Texture::load(get_test_input() / "AngryCat.png");
    auto rectangle = pkzo::Texture::load(get_test_input() / "rectangle.png");

    auto diff = pkzo::diff(angry_cat, rectangle);
    EXPECT_TEXTURE_REF_EQ(diff);
}
