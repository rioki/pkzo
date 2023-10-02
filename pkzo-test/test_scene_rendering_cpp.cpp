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

#include <pkzo/Window.h>
#include <pkzo/opengl.h>
#include <pkzo-three/Scene.h>

#include <glm/gtc/matrix_transform.hpp>

#include <gtest/gtest.h>
#include "pkzo_test.h"

#if 0
TEST(Scene_Rendering, GRAPH_box_and_light)
{
    // Note: The scene is created before the OpenGL context, because it needs to be able
    // to live outside of the context.

    auto scene = std::make_shared<pkzo::three::Scene>();

    // camera
    auto camera_t = pkzo::look_at(glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    auto camera = std::make_shared<pkzo::Camera>(camera_t);
    scene->add_node(camera);

    // lights
    auto ambient_light = std::make_shared<pkzo::AmbientLight>(pkzo::rgb(8,27,41));
    scene->add_node(ambient_light);

    auto dir_light_t = pkzo::look_at(glm::vec3(0.0f), glm::vec3(-1.0f, -0.7f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    auto dit_light = std::make_shared<pkzo::DirectionalLight>(dir_light_t, pkzo::rgb(250,243,182));
    scene->add_node(dit_light);

    // action
    auto spehre_t = glm::mat4(1.0f);
    auto sphere_m = std::make_shared<pkzo::Material>():
    auto sphere = std::make_shared<pkzo::SphereGeometry>(spehre_t, sphere_m);
    scene->add_node(sphere);

    { // With OpenGL context.
        auto window = pkzo::Window{{800,600}, "Test"};
        auto gl_trace = pkzo::opengl::Trace{};

        scene->activate();

        window.get_draw_signal().connect([scene] () {
            scene->draw();
        });

        window->draw();
        window->draw();
        window->draw();

        EXPECT_TEXTURE_REF_EQ(window.save_screen());

        scene->deactivate();
    }

    // This happens anyway, but it's part of the test, make it explicit.
    scene = nullptr;
}

#endif
