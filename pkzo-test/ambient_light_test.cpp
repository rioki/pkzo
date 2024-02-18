// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include <pkzo/Window.h>
#include <pkzo/Scene.h>
#include <pkzo/AmbientLight.h>


using namespace testing;

TEST(AmbientLight, create)
{
    auto light = pkzo::AmbientLight();

    EXPECT_EQ(light.get_parent(), nullptr);
    EXPECT_EQ(light.get_type(), "AmbientLight");
    EXPECT_GLM_NEAR(light.get_color(), glm::vec3(0.2f), 1e-4f);
}

TEST(AmbientLight, init)
{
    auto light = pkzo::AmbientLight(glm::vec3(0.5f, 0.1f, 0.2f));

    EXPECT_GLM_NEAR(light.get_color(), glm::vec3(0.5f, 0.1f, 0.2f), 1e-4f);
}

TEST(AmbientLight, serialzie)
{
    auto light = std::make_unique<pkzo::AmbientLight>(glm::vec3(0.5f, 0.1f, 0.2f));

    auto orig = pkzo::Scene();
    orig.add_child(std::move(light));

    auto file = get_test_output() / "AmbientLight_serialzie.json";
    orig.save(file);

    auto loaded = pkzo::Scene(file);

    auto lights = loaded.find_descendants<pkzo::AmbientLight>();
    ASSERT_EQ(lights.size(), 1u);
    EXPECT_GLM_NEAR(lights[0]->get_color(), glm::vec3(0.5f, 0.1f, 0.2f), 1e-4f);
}
