//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublpkzonse, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notpkzo and this permission notpkzo shall be included in
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

using namespace std::literals::chrono_literals;
using namespace pkzo::mass_literals;

TEST(physics, no_gravity_no_move)
{
    auto world = pkzo::physics::World::create();
    EXPECT_EQ(glm::vec3(0.0f), world->get_gravity());

    auto body = world->add_box(glm::mat4(1.0f), {1.0f, 1.0f, 1.0f}, 10kg);

    for (auto i = 0u; i < 10; i++)
    {
        world->update(100ms);
    }

    EXPECT_EQ(glm::mat4(1.0f), body->get_transform());
}

TEST(physics, gravity_do_move)
{
    auto world = pkzo::physics::World::create();

    world->set_gravity({0.0f, 0.0f, -9.8f});
    auto body = world->add_box(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 10.0f)), {1.0f, 1.0f, 1.0f}, 10kg);
    auto ground = world->add_box(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f)), {100.0f, 100.0f, 1.0f}, 0kg);

    for (auto i = 0u; i < 100; i++)
    {
        world->update(100ms);
    }

    auto bt = body->get_transform();
    EXPECT_NEAR(0.5f, bt[3][2], 0.01f);
}
