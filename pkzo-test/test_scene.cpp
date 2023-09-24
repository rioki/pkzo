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

#include <pkzo-three/Scene.h>
#include <glm/gtc/matrix_transform.hpp>

#include <gtest/gtest.h>

TEST(Scene, get_scene_returns_self)
{
    pkzo::three::Scene scene;
    ASSERT_EQ(scene.get_scene(), &scene);
}

TEST(Scene, get_scene_returns_correct_scene)
{
    pkzo::three::Scene     scene;
    pkzo::three::SceneNode child_node;
    pkzo::three::SceneNode grand_child_node;

    child_node.set_parent(&scene);
    grand_child_node.set_parent(&child_node);

    ASSERT_EQ(child_node.get_scene(), &scene);
    ASSERT_EQ(grand_child_node.get_scene(), &scene);
}
