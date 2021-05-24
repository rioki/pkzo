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

#include "Pawn.h"
#include "PhysicalBox.h"

using namespace pkzo::mass_literals;

namespace boxes
{
    Game::Game(int argc, const char* argv[])
    {
        auto user_folder = pkzo::get_user_folder() / "pkzo" / "boxes";
        std::filesystem::create_directories(user_folder);

        auto settings_file = user_folder / "settings.json";
        if (std::filesystem::exists(settings_file))
        {
            settings.load(settings_file);
        }

        main.on_tick([this] (auto dt) {
            if (scene)
            {
                scene->update(dt);
            }
        });

        auto resolution = settings.get_value("Graphic", "resolution", glm::uvec2(800, 600));
        auto fullscreen = settings.get_value("Graphic", "fullscreen", false);
        auto& window = main.open_window(resolution, fullscreen ? pkzo::WindowMode::FULLSCREEN : pkzo::WindowMode::STATIC, "Pkzo - Boxes");
        window.on_draw([this] () {
            if (scene && camera)
            {
                scene->draw(*camera);
            }
        });

        create_pawn();
        create_test_scene();
    }

    Game::~Game()
    {
        try
        {
            auto settings_file = pkzo::get_user_folder() / "pkzo" / "boxes" / "settings.json";
            settings.save(settings_file);
        }
        catch (const std::exception& ex)
        {
            DBG_TRACE(ex.what());
        }
    }

    int Game::run()
    {
        main.run();
        return 0;
    }

    void Game::create_pawn()
    {
        pawn = std::make_shared<Pawn>();
        pawn->set_fore_key(settings.get_value("Pawn", "fore_key", pawn->get_fore_key()));
        pawn->set_back_key(settings.get_value("Pawn", "back_key", pawn->get_back_key()));
        pawn->set_left_key(settings.get_value("Pawn", "left_key", pawn->get_left_key()));
        pawn->set_right_key(settings.get_value("Pawn", "right_key", pawn->get_right_key()));
        pawn->set_mouse_sensitivity(settings.get_value("Pawn", "mouse_sensitivity", pawn->get_mouse_sensitivity()));
        pawn->set_invert_mouse(settings.get_value("Pawn", "invert_mouse", pawn->get_invert_mouse()));

        auto& keyboard = main.get_keyboard();
        keyboard.on_key_down([this] (auto mod, auto key) {
            pawn->handle_key_down(key);
        });
        keyboard.on_key_up([this] (auto mod, auto key) {
            pawn->handle_key_up(key);
        });

        auto& mouse = main.get_mouse();
        mouse.on_move([this] (auto pos, auto rel) {
            pawn->handle_mouse_move(rel);
        });
        mouse.on_button_down([this] (auto button, auto pos) {
            pawn->handle_mouse_down(button);
        });
        mouse.on_button_up([this] (auto button, auto pos) {
            pawn->handle_mouse_up(button);
        });
    }

    void Game::create_test_scene()
    {
        scene = std::make_shared<pkzo::Scene>();
        scene->set_gravity({0.0f, 0.0f, -9.81f});

        pawn->set_transform(pkzo::position(-3.0f, 0.5f, 5.0f));
        scene->add_node(pawn);
        camera = pawn->get_camera();

        // Lights
        auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
        scene->add_node(light0);

        auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
        auto light1 = std::make_shared<pkzo::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
        scene->add_node(light1);

        auto light2 = std::make_shared<pkzo::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
        scene->add_node(light2);

        // Action
        auto ground_material = pkzo::make_simple_material({0.9f, 0.9f, 0.9f}, {0.04f, 0.04f, 0.04f}, 0.15f);
        auto ground = std::make_shared<pkzo::Box>(glm::translate(glm::mat4{1.0f}, {0.0f, 0.0f, -0.5f}), glm::vec3(100.0f, 100.0f, 1.0f), ground_material);
        scene->add_node(ground);

        auto box_material = pkzo::make_simple_material({0.1f, 0.1f, 0.9f}, {0.04f, 0.04f, 0.04f}, 0.15f);
        for (auto i = 0; i < 3; i++)
        {
            for (auto j = 0; j < 3; j++)
            {
                for (auto k = 0; k < 3; k++)
                {
                    auto box = std::make_shared<PhysicalBox>(pkzo::position(-2.5f + i, -2.5f + j, 5.0f + k), glm::vec3(0.5f), 10kg, box_material);
                    scene->add_node(box);
                }
            }
        }
    }
}

int main(int argc, const char* argv[])
{
    try
    {
        boxes::Game game(argc, argv);
        return game.run();
    }
    catch (const std::exception& ex)
    {
        show_message_box(pkzo::MessageBoxIcon::ICON_ERROR, "Unhandled Exception", ex.what());
        return -1;
    }
    catch (...)
    {
        show_message_box(pkzo::MessageBoxIcon::ICON_ERROR, "Unhandled Exception", "Unknown exception.");
        return -1;
    }
}
