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

using namespace pkzo::test;

TEST(Phong, shapes)
{
    pkzo::Window window({800, 600}, pkzo::WindowMode::STATIC, __FUNCTION__);

    pkzo::three::Scene scene;

    auto box = std::make_shared<pkzo::three::Box>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, 0.0f}), glm::vec3(1.0f));
    scene.add_child(box);

    auto sphere = std::make_shared<pkzo::three::Sphere>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), 0.5f);
    scene.add_child(sphere);

    auto light0 = std::make_shared<pkzo::three::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene.add_child(light0);

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    auto light1 = std::make_shared<pkzo::three::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
    scene.add_child(light1);

    auto light2 = std::make_shared<pkzo::three::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
    scene.add_child(light2);

    auto ct = glm::mat4(1.0f);
    ct = glm::translate(ct, {0.0f, 0.0f, 5.0f});
    auto camera = std::make_shared<pkzo::three::Camera>();
    camera->look_at({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    camera->set_resolution(window.get_size());
    scene.add_child(camera);

    window.on_draw([&] () {
        scene.draw(*camera);
    });
    window.draw();
    window.draw();

    auto test_image = window.save();
    ASSERT_NE(nullptr, test_image);
    EXPECT_TEXTURE_REF_EQ(*test_image);
}