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

#include <pkzo/Settings.h>

TEST(Settings, initial_values)
{
    pkzo::Settings settings;
    EXPECT_EQ(false, settings.get_value("Test", "test", false));
    EXPECT_EQ(36u, settings.get_value("Test", "awnser", 36u));
    EXPECT_EQ(37.0f, settings.get_value("Test", "high_precision_awnser", 37.0f));
    EXPECT_GLM_EQ(glm::vec3(1.2f, 2.3f, 3.4f), settings.get_value("Test", "some_vector", glm::vec3(1.2f, 2.3f, 3.4f)));
}

TEST(Settings, set_and_get)
{
    pkzo::Settings settings;
    settings.set_value("Test", "test", true);
    settings.set_value("Test", "awnser", 42u);
    settings.set_value("Test", "high_precision_awnser", 42.0f);
    settings.set_value("Test", "some_vector", glm::vec3(5.4f, 3.2f, 1.0f));

    EXPECT_EQ(true, settings.get_value("Test", "test", false));
    EXPECT_EQ(42u, settings.get_value("Test", "awnser", 36u));
    EXPECT_EQ(42.0f, settings.get_value("Test", "high_precision_awnser", 37.0f));
    EXPECT_GLM_EQ(glm::vec3(5.4f, 3.2f, 1.0f), settings.get_value("Test", "some_vector", glm::vec3(1.2f, 2.3f, 3.4f)));
}

TEST(Settings, save_and_load)
{
    pkzo::Settings a;
    a.set_value("Test", "test", true);
    a.set_value("Test", "awnser", 42);
    a.set_value("Test", "high_precision_awnser", 42.0f);
    a.set_value("Test", "some_vector", glm::vec3(5.4f, 3.2f, 1.0f));
    a.save(pkzo::test::get_test_temp() / "save_and_load.json");

    pkzo::Settings b;
    b.load(pkzo::test::get_test_temp() / "save_and_load.json");
    EXPECT_EQ(true, b.get_value("Test", "test", false));
    EXPECT_EQ(42u, b.get_value("Test", "awnser", 36u));
    EXPECT_EQ(42.0f, b.get_value("Test", "high_precision_awnser", 37.0f));
    EXPECT_GLM_EQ(glm::vec3(5.4f, 3.2f, 1.0f), b.get_value("Test", "some_vector", glm::vec3(1.2f, 2.3f, 3.4f)));
}