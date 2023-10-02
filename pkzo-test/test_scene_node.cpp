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

#include <pkzo-three/SceneNode.h>
#include <pkzo-three/SceneGroup.h>
#include <glm/gtc/matrix_transform.hpp>

#include <gtest/gtest.h>
#include "glm_gtest.h"

TEST(SceneNode, default_constructor)
{
    pkzo::three::SceneNode node;
    EXPECT_EQ(node.get_transform(), glm::mat4(1.0f));
    EXPECT_EQ(node.get_parent(), nullptr);
}

TEST(SceneNode, set_transform)
{
    pkzo::three::SceneNode node;
    glm::mat4 new_transform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

    node.set_transform(new_transform);
    EXPECT_EQ(node.get_transform(), new_transform);
}

TEST(SceneNode, get_global_transform)
{
    glm::mat4 root_transform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
    glm::mat4 child_transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 expected_global_transform = root_transform * child_transform;

    pkzo::three::SceneGroup root(root_transform);
    pkzo::three::SceneNode child(child_transform);
    root.add_node(child);

    EXPECT_EQ(child.get_global_transform(), expected_global_transform);
}

TEST(SceneNode, set_parent)
{
    pkzo::three::SceneNode node;
    pkzo::three::SceneNode new_parent;

    node.set_parent(&new_parent);
    EXPECT_EQ(node.get_parent(), &new_parent);
}


TEST(SceneNode, look_at)
{
    glm::vec3 eye(0.0f, 0.0f, 5.0f);
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::mat4 expected = glm::inverse(glm::lookAt(eye, center, up));
    glm::mat4 result   = pkzo::three::look_at(eye, center, up);

    EXPECT_GLM_NEAR(expected, result, 1e-4f);
}

TEST(SceneNode, look_at_eye_and_center_are_same)
{
    glm::vec3 eye(1.0f, 1.0f, 1.0f);
    glm::vec3 center(1.0f, 1.0f, 1.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::mat4 result = pkzo::three::look_at(eye, center, up);

    // This should produce an identity matrix, but it's an edge case to be avoided in practice.
    EXPECT_GLM_NEAR(glm::mat4(1.0f), result, 1e-4f);
}
