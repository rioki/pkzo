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
#include "Game.h"

namespace boxes
{
    Game::Game(int argc, const char* argv[])
    : Engine("boxes", argc, argv)
    {
        create_test_scene();
    }

    void Game::create_test_scene()
    {
        auto scene = std::make_shared<pkzo::Scene>();

        // Camera
        auto camera = std::make_shared<pkzo::PerspectiveCamera>(pkzo::lookat({-2.0f, 0.5f, 1.0f}, {0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}));
        scene->add_node(camera);

        // Lights
        auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
        scene->add_node(light0);

        auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
        auto light1 = std::make_shared<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
        scene->add_node(light1);

        auto light2 = std::make_shared<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
        scene->add_node(light2);

        // Action
        auto ground = std::make_shared<pkzo::Box>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, -0.5f}), glm::vec3(10.0f, 10.0f, 1.0f));
        scene->add_node(ground);

        change_scene(scene, camera);
    }
}

int main(int argc, const char* argv[])
{
    boxes::Game game(argc, argv);
    return game.run();
}
