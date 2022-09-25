// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"

#include "MockGraphicSystem.h"
#include "MockRenderer.h"

using namespace ::testing;
using namespace glm;

TEST(BoxVisual, default_contruct)
{
    auto visual = ice::BoxVisual();
    EXPECT_GLM_NEAR(glm::mat4(1.0f), visual.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec3(1.0f), visual.get_size(), 1e-4f);
    EXPECT_EQ(ice::Visual::get_default_material(), visual.get_material());
}

TEST(BoxVisual, init)
{
    auto tra      = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 2.0f, -3.0f));
    auto material = std::make_shared<ice::Material>();
    auto visual   = ice::BoxVisual(tra, glm::vec3(0.1, 0.2, 0.3), material);
    EXPECT_GLM_NEAR(tra, visual.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec3(0.1, 0.2, 0.3), visual.get_size(), 1e-4f);
    EXPECT_EQ(material, visual.get_material());
}

TEST(BoxVisual, registers_on_renderer)
{
    auto engine = ice::Engine{};
    auto gs = engine.start_system<StrictMock<ice::test::MockGraphicSystem>>();

    auto renderer = std::make_unique<StrictMock<ice::test::MockRenderer>>();

    auto transform  = inverse(lookAt(vec3(-10.0f, 0.5f, 2.0f), vec3(0.0f), vec3(0.0f, 0.0f, 1.0f)));
    auto material   = std::make_shared<ice::Material>();
    auto size       = glm::vec3(0.4f, 0.5f, 0.6f);
    auto vis_tra    = scale(transform, size);
    const auto cmat = std::shared_ptr<const ice::Material>(material);

    InSequence s;

    EXPECT_CALL(*gs, create_scene_renderer())
        .WillOnce(Return(renderer.get()));

    EXPECT_CALL(*renderer, add_geometry(vis_tra, _, cmat))
        .WillOnce(Return(46));
    EXPECT_CALL(*renderer, remove_geometry(46));

    EXPECT_CALL(*gs, release_scene_renderer(renderer.get()));

    auto scene = std::make_shared<ice::Scene>();

    auto camera = std::make_shared<ice::BoxVisual>(transform, size, material);
    scene->add_node(camera);

    engine.set_scene(scene);

    engine.run(5u);
}
