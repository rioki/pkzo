// pkzo
// Copyright 2023-2024 Sean Farrell <sean.farrell@rioki.org>
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
#include <pkzo/Camera.h>
#include <pkzo/DirectionalLight.h>
#include <pkzo/AmbientLight.h>
#include <pkzo/BoxGeometry.h>
#include <pkzo/SphereGeometry.h>

TEST(Renderer, render_shapes)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Pkzo Test", {800, 600}};

    auto scene = std::make_shared<pkzo::Scene>();

    auto ct = glm::inverse(glm::lookAt(glm::vec3{-5.0f, 1.0f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}));
    scene->add_child(std::make_unique<pkzo::Camera>(ct, 90.0f));

    // lights
    scene->add_child(std::make_unique<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2}));

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    scene->add_child(std::make_unique<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573)));

    scene->add_child(std::make_unique<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329)));

    // action
    auto material = std::make_shared<pkzo::Material>();
    material->set_base_color_factor(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));

    scene->add_child(std::make_unique<pkzo::BoxGeometry>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), glm::vec3(1.0f), material));

    scene->add_child(std::make_unique<pkzo::SphereGeometry>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), 1.0f, material));

    scene->activate();

    window.on_draw([&]() {
        scene->draw(window.get_drawable_size());
    });

    window.draw();
    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_NEAR(window.get_screenshot(), 200.0f);
}

TEST(Renderer, materials)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, "Pkzo Test", {800, 600}};

    auto scene = std::make_shared<pkzo::Scene>();

    auto ct = glm::inverse(glm::lookAt(glm::vec3{-5.0f, 1.0f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}));
    scene->add_child(std::make_unique<pkzo::Camera>(ct, 90.0f));

    // lights
    scene->add_child(std::make_unique<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2}));

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    scene->add_child(std::make_unique<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573)));

    scene->add_child(std::make_unique<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329)));

    // action
    auto material = std::make_shared<pkzo::Material>(testing::get_test_input() / "materials/TestOrange.json");

    scene->add_child(std::make_unique<pkzo::BoxGeometry>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), glm::vec3(1.0f), material));

    scene->add_child(std::make_unique<pkzo::SphereGeometry>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, -0.0f}), 1.0f, material));

    scene->activate();

    window.on_draw([&]() {
        scene->draw(window.get_drawable_size());
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}
