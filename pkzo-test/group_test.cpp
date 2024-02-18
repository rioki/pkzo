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
#include <pkzo/Group.h>
#include <pkzo/Scene.h>

using namespace testing;

class TestNode : public pkzo::SceneNode
{
public:
    unsigned int id = 0;

    TestNode(unsigned int id = 0) noexcept
    : id(id) {}

    TestNode(const TestNode& other)
    : pkzo::SceneNode(other), id(other.id + 1) {}

    std::string get_type() const noexcept override
    {
        return "TestNode";
    }

    std::unique_ptr<SceneNode> clone() const noexcept
    {
        return std::make_unique<TestNode>(*this);
    }

    void serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const override
    {
        SceneNode::serialize(j, base_dir);
        j["id"] = id;
    }

    void deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
{
        SceneNode::deserialize(j, base_dir);
        id = j.value("id", id);
    }
};

class TestGroup : public pkzo::Group
{
public:
    TestGroup() noexcept
    {
        add_child(node);
    }

    TestGroup(const TestGroup& other)
    : pkzo::Group(other), node(other.node)
    {
        add_child(node);
    }

    std::string get_type() const noexcept override
    {
        return "TestGroup";
    }

    std::unique_ptr<SceneNode> clone() const noexcept
    {
        return std::make_unique<TestGroup>(*this);
    }

    // NOTE: If you want to serialize unmanged nodes, you need to do this manually.
    // e.g.
    // auto jnode = json::object();
    // node.serialize(jnode, base_dir);
    // j["node"] = jnode;

private:
    TestNode node = {100};
};

PKZO_THREE_REGISTER_TYPE(TestNode);
PKZO_THREE_REGISTER_TYPE(TestGroup);

TEST(Group, add_unique_ptr)
{
    auto group = pkzo::Group();

    auto node = std::make_unique<TestNode>();
    group.add_child(std::move(node));

    ASSERT_EQ(1, group.get_children().size());
}

TEST(Group, add_static)
{
    auto group = pkzo::Group();

    auto node = TestNode();
    group.add_child(node);

    ASSERT_EQ(1, group.get_children().size());
}

TEST(Group, unmanaged_not_serisalized)
{
    auto orig = pkzo::Scene();
    auto group = std::make_unique<TestGroup>();

    group->add_child(std::make_unique<TestNode>(1000));
    orig.add_child(std::move(group));

    auto file = get_test_output() / "Group_unmanaged_not_serisalized.json";
    orig.save(file);

    auto loaded = pkzo::Scene(file);

    auto nodes = loaded.find_descendants<TestNode>();
    ASSERT_EQ(2, nodes.size());
    EXPECT_EQ(100, nodes[0]->id);
    EXPECT_EQ(1000, nodes[1]->id);
}

TEST(Group, unmanaged_not_cloned)
{
    auto orig = pkzo::Scene();
    auto group = std::make_unique<TestGroup>();

    group->add_child(std::make_unique<TestNode>(1000));
    orig.add_child(std::move(group));

    auto clone = rex::dynamic_unique_cast<pkzo::Scene>(orig.clone());

    ASSERT_NE(clone, nullptr);

    auto nodes = clone->find_descendants<TestNode>();
    ASSERT_EQ(2, nodes.size());
    EXPECT_EQ(1001, nodes[0]->id);
    EXPECT_EQ(101,  nodes[1]->id);
}
