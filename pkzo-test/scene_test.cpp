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

TEST(Scene, create)
{
    auto scene = pkzo::Scene();

    EXPECT_EQ(scene.get_parent(), nullptr);
    EXPECT_EQ(scene.get_children().size(), 0u);
}

class TestSceneNode : public pkzo::SceneNode
{
public:
    TestSceneNode() = default;

    TestSceneNode(const TestSceneNode& other)
    : SceneNode(other) {}

    std::string get_type() const noexcept override
    {
        return "TestSceneNode";
    }

    std::unique_ptr<SceneNode> clone() const noexcept override
    {
        return std::make_unique<TestSceneNode>(*this);
    }
};

TEST(Scene, add_child_on_scene)
{
    auto scene = pkzo::Scene();
    auto node = std::make_unique<TestSceneNode>();
    auto ptr = node.get();

    scene.add_child(std::move(node));

    EXPECT_EQ(ptr->get_parent(), &scene);
    EXPECT_EQ(scene.get_children().size(), 1u);
    EXPECT_EQ(scene.get_children()[0], ptr);
}

TEST(Scene, add_child_on_group)
{
    auto scene = pkzo::Scene();
    auto group = std::make_unique<pkzo::Group>();
    auto node = std::make_unique<TestSceneNode>();

    auto g = group.get();
    auto n = node.get();

    group->add_child(std::move(node));
    scene.add_child(std::move(group));

    EXPECT_EQ(n->get_parent(), g);
    EXPECT_EQ(g->get_children().size(), 1u);
    EXPECT_EQ(g->get_children()[0], n);
}

TEST(Scene, add_child_on_group_after_attach)
{
    auto scene = pkzo::Scene();
    auto group = std::make_unique<pkzo::Group>();
    auto node = std::make_unique<TestSceneNode>();

    auto g = group.get();
    auto n = node.get();

    scene.add_child(std::move(group));
    g->add_child(std::move(node));

    EXPECT_EQ(n->get_parent(), g);
    EXPECT_EQ(g->get_children().size(), 1u);
    EXPECT_EQ(g->get_children()[0], n);
}

// This test would crash if no OpenGL context is available;
// thus the activate / deactivate mechanic was introduced.
TEST(Scene, create_box_geometry_outside_of_glcontext)
{
    auto scene = pkzo::Scene();
    auto box = std::make_unique<pkzo::BoxGeometry>();

    scene.add_child(std::move(box));
}

TEST(Scene, save_and_load_empty_scene)
{
    auto orig = pkzo::Scene();

    auto file = get_test_output() / "save_and_load_empty_scene.json";
    orig.save(file);

    auto loaded = pkzo::Scene(file);

    EXPECT_EQ(file, loaded.get_file());
    EXPECT_EQ(orig.get_children().size(), loaded.get_children().size());
}

