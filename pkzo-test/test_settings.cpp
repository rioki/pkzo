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

TEST(Settings, fall_back)
{
    auto settings = pkzo::Settings{};

    EXPECT_EQ("some string value", settings.get_value("test", "string", "some string value"));
    EXPECT_EQ(6.9f, settings.get_value("test", "float", 6.9f));
    EXPECT_EQ(42, settings.get_value("test", "int", 42));
}

TEST(Settings, set_get)
{
    auto settings = pkzo::Settings{};

    settings.set_value("test", "string", "currect string");
    settings.set_value("test", "float", -13.13f);
    settings.set_value("test", "int", -1337);

    EXPECT_EQ("currect string", settings.get_value("test", "string", "some string value"));
    EXPECT_EQ(-13.13f, settings.get_value("test", "float", 6.9f));
    EXPECT_EQ(-1337, settings.get_value("test", "int", 42));
}

TEST(Settings, save_load)
{
    auto file = pkzo::test::get_test_output() / (pkzo::test::get_test_name() + ".json");

    auto a = pkzo::Settings{};

    a.set_value("test", "string", "currect string");
    a.set_value("test", "float", -13.13f);
    a.set_value("test", "int", -1337);
    a.save(file);

    auto b = pkzo::Settings{};
    b.load(file);

    EXPECT_EQ("currect string", b.get_value("test", "string", "some string value"));
    EXPECT_EQ(-13.13f, b.get_value("test", "float", 6.9f));
    EXPECT_EQ(-1337, b.get_value("test", "int", 42));
}

TEST(Settings, glm)
{
    auto settings = pkzo::Settings{};

    settings.set_value("test", "uvec2", glm::uvec2(800u, 600u));
    settings.set_value("test", "vec4",  glm::vec4(1.2f, 2.3f, 3.4f, 4.5f));

    EXPECT_GLM_EQ(glm::uvec2(800, 600), settings.get_value("test", "uvec2", glm::uvec2(0u)));
    EXPECT_GLM_EQ(glm::vec4(1.2f, 2.3f, 3.4f, 4.5f), settings.get_value("test", "vec4",glm::vec4(0.0f)));
}

TEST(Settings, glm_save_load)
{
    auto file = pkzo::test::get_test_output() / (pkzo::test::get_test_name() + ".json");

    auto a = pkzo::Settings{};

    a.set_value("test", "uvec2", glm::uvec2(800u, 600u));
    a.set_value("test", "vec4",  glm::vec4(1.2f, 2.3f, 3.4f, 4.5f));
    a.save(file);

    auto b = pkzo::Settings{};
    b.load(file);

    EXPECT_GLM_EQ(glm::uvec2(800, 600), b.get_value("test", "uvec2", glm::uvec2(0u)));
    EXPECT_GLM_EQ(glm::vec4(1.2f, 2.3f, 3.4f, 4.5f), b.get_value("test", "vec4",glm::vec4(0.0f)));
}