//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicese, and/or sell
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

#include "pysics_mock.h"

using namespace std::literals::chrono_literals;
using namespace pkzo::mass_literals;

TEST(Scene, default_contruct)
{
    pkzo::Scene node;
}

TEST(Scene, substitute_physics)
{
    auto mock_physics = std::make_shared<pkzo::test::MockWorld>();

    pkzo::Scene scene(mock_physics);

    EXPECT_EQ(mock_physics, scene.get_physics());
}

TEST(Scene, gravity)
{
    pkzo::Scene scene;

    EXPECT_EQ(glm::vec3(0.0f), scene.get_gravity());
    scene.set_gravity({0.0f, 0.0f, -9.81f});
    EXPECT_EQ(glm::vec3(0.0f, 0.0f, -9.81f), scene.get_gravity());
}

TEST(Scene, physics_simulation)
{
    auto dummy_material = std::make_shared<pkzo::Material>();

    pkzo::Scene scene;
    scene.set_gravity({0.0f, 0.0f, -9.8f});

    auto ground = std::make_shared<pkzo::Box>(pkzo::position(0.0f, 0.0f, -0.5f), glm::vec3(100.0f, 100.0f, 1.0), dummy_material);
    scene.add_node(ground);

    auto box = std::make_shared<pkzo:: Body>(pkzo::position(0.0f, 0.0f, 10.0f), 10kg);
    auto box_geom = std::make_shared<pkzo::Box>(pkzo::position(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), dummy_material);
    box->add_node(box_geom);
    scene.add_node(box);

    for (auto i = 0u; i < 1000; i++)
    {
        scene.update(10ms);
    }

    auto bt = box->get_transform();
    EXPECT_NEAR(0.5f, bt[3][2], 0.01f);
}