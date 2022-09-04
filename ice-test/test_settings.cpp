// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/Settings.h>

#include <ice/ice.h>

TEST(Settings, fall_back)
{
    auto settings = ice::Settings{};

    EXPECT_EQ("some string value", settings.get_value("test", "string", "some string value"));
    EXPECT_EQ(6.9f, settings.get_value("test", "float", 6.9f));
    EXPECT_EQ(42, settings.get_value("test", "int", 42));
}

TEST(Settings, set_get)
{
    auto settings = ice::Settings{};

    settings.set_value("test", "string", "currect string");
    settings.set_value("test", "float", -13.13f);
    settings.set_value("test", "int", -1337);

    EXPECT_EQ("currect string", settings.get_value("test", "string", "some string value"));
    EXPECT_EQ(-13.13f, settings.get_value("test", "float", 6.9f));
    EXPECT_EQ(-1337, settings.get_value("test", "int", 42));
}

TEST(Settings, save_load)
{
    auto file = ice::test::get_test_output() / (ice::test::get_test_name() + ".json");

    auto a = ice::Settings{};

    a.set_value("test", "string", "currect string");
    a.set_value("test", "float", -13.13f);
    a.set_value("test", "int", -1337);
    a.save(file);

    auto b = ice::Settings{};
    b.load(file);

    EXPECT_EQ("currect string", b.get_value("test", "string", "some string value"));
    EXPECT_EQ(-13.13f, b.get_value("test", "float", 6.9f));
    EXPECT_EQ(-1337, b.get_value("test", "int", 42));
}

TEST(Settings, glm)
{
    auto settings = ice::Settings{};

    settings.set_value("test", "uvec2", glm::uvec2(800u, 600u));
    settings.set_value("test", "vec4",  glm::vec4(1.2f, 2.3f, 3.4f, 4.5f));

    EXPECT_GLM_EQ(glm::uvec2(800, 600), settings.get_value("test", "uvec2", glm::uvec2(0u)));
    EXPECT_GLM_EQ(glm::vec4(1.2f, 2.3f, 3.4f, 4.5f), settings.get_value("test", "vec4",glm::vec4(0.0f)));
}

TEST(Settings, glm_save_load)
{
    auto file = ice::test::get_test_output() / (ice::test::get_test_name() + ".json");

    auto a = ice::Settings{};

    a.set_value("test", "uvec2", glm::uvec2(800u, 600u));
    a.set_value("test", "vec4",  glm::vec4(1.2f, 2.3f, 3.4f, 4.5f));
    a.save(file);

    auto b = ice::Settings{};
    b.load(file);

    EXPECT_GLM_EQ(glm::uvec2(800, 600), b.get_value("test", "uvec2", glm::uvec2(0u)));
    EXPECT_GLM_EQ(glm::vec4(1.2f, 2.3f, 3.4f, 4.5f), b.get_value("test", "vec4",glm::vec4(0.0f)));
}