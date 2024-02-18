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
#include <pkzo/BoxGeometry.h>


using namespace testing;

TEST(BoxGeometry, create)
{
    auto box = pkzo::BoxGeometry();

    EXPECT_EQ(box.get_parent(), nullptr);
    EXPECT_EQ(box.get_type(), "BoxGeometry");
    EXPECT_EQ(box.get_size(), glm::vec3(1.0f));
    EXPECT_EQ(box.get_transform(), glm::mat4(1.0f));
    EXPECT_EQ(box.get_material(), nullptr);
}

TEST(BoxGeometry, init)
{
    auto material = std::make_shared<pkzo::Material>(get_test_input() / "materials/TestOrange.json");

    auto box = pkzo::BoxGeometry(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), glm::vec3(1.0f, 0.5f, 0.4f), material);

    EXPECT_EQ(box.get_size(), glm::vec3(1.0f, 0.5f, 0.4f));
    EXPECT_GLM_NEAR(box.get_transform(), glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), 1e-4f);
    EXPECT_EQ(box.get_material(), material);
}

TEST(BoxGeometry, serialzie)
{
    auto material = std::make_shared<pkzo::Material>(get_test_input() / "materials/TestOrange.json");

    auto box = std::make_unique<pkzo::BoxGeometry>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), glm::vec3(1.0f, 0.5f, 0.4f), material);

    auto orig = pkzo::Scene();
    orig.add_child(std::move(box));

    auto file = get_test_output() / "BoxGeometry_serialzie.json";
    orig.save(file);

    auto loaded = pkzo::Scene(file);

    auto boxes = loaded.find_descendants<pkzo::BoxGeometry>();
    ASSERT_EQ(boxes.size(), 1u);
    EXPECT_EQ(boxes[0]->get_size(), glm::vec3(1.0f, 0.5f, 0.4f));
    EXPECT_GLM_NEAR(boxes[0]->get_transform(), glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), 1e-4f);
    ASSERT_NE(boxes[0]->get_material(), nullptr);
    EXPECT_EQ(boxes[0]->get_material()->get_file(), material->get_file());
}
