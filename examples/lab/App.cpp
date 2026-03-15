// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "App.h"

#include "tinyformat.h"

#include <pkzo/debug.h>
#include "DebugOverlay.h"
#include "MainMenu.h"
#include "Pawn.h"
#include "MaterialTestScene.h"
#include "PhysicsTestScene.h"

namespace lab
{
    using pkzo::check;
    using fsec = std::chrono::duration<float>;

    App::App(int argc, char* argv[])
    {
        pkzo::on_quit([&] () {
            running = false;
        });

        window = std::make_unique<pkzo::Window>(pkzo::Window::Init{
            .title = tfm::format("pkzo lab %s", VERSION),
            .size  = glm::uvec2(1600, 900),
            .state = pkzo::WindowState::WINDOW,
        });
        window->on_draw([this] (auto& gc) { handle_draw(gc); });

        mouse = std::make_unique<pkzo::Mouse>();
        mouse->on_move([this] (auto ev)            { handle_mouse_move(ev.releative); } );
        mouse->on_button_down([this] (auto ev)  { handle_mouse_button_down(ev.position, ev.button); });
        mouse->on_button_up([this] (auto ev)    { handle_mouse_button_up(ev.position, ev.button); });

        keyboard = std::make_unique<pkzo::Keyboard>();
        keyboard->on_key_down([this] (auto mod, auto key, auto scan) { handle_key_down(scan); } );
        keyboard->on_key_up([this] (auto mod, auto key, auto scan)   { handle_key_up(scan); } );

        debug_overlay = std::make_unique<DebugOverlay>(window->get_resolution());
        next_screen   = std::make_unique<MainMenu>(*this, window->get_resolution());
    }

    App::~App() = default;

    void App::show_main_menu()
    {
        next_screen = std::make_unique<MainMenu>(*this, window->get_resolution());
        next_scene  = std::unique_ptr<pkzo3d::Scene>();
    }

    void App::start_material_test()
    {
        next_screen = std::unique_ptr<pkzo::Screen>();
        next_scene  = std::make_unique<MaterialTestScene>();
    }

    void App::start_physics_test()
    {
        next_screen = std::unique_ptr<pkzo::Screen>();
        next_scene  = std::make_unique<PhysicsTestScene>();
    }

    int App::run()
    {
        last_tick = std::chrono::steady_clock::now();
        running   = true;
        while (running)
        {
            tick();
        }
        return 0;
    }

    void App::stop()
    {
        running = false;
    }

    void App::tick()
    {
        if (next_screen)
        {
            screen      = std::move(*next_screen);
            next_screen = std::nullopt;
        }

        if (next_scene)
        {
            scene      = std::move(*next_scene);
            next_scene = std::nullopt;
            if (scene)
            {
                pawn = scene->add<Pawn>({
                    .transform = pkzo3d::position(glm::vec3(0.0, 0.0, 0.0f))
                });
                window->capture_mouse();
            }
            else
            {
                pawn = nullptr;
                window->release_mouse();
            }
        }

        auto now = std::chrono::steady_clock::now();
        auto dt  = std::chrono::duration_cast<fsec>(now - last_tick).count();
        last_tick = now;

        pkzo::rotue_events();

        if (scene)         scene->update(dt);
        if (screen)        screen->update(dt);
        if (debug_overlay) debug_overlay->update(dt);

        check(window);
        window->draw();
    }

    void App::handle_draw(pkzo::GraphicContext& gc)
    {
        if (scene)         scene->draw(gc);
        if (screen)        screen->draw(gc);
        if (debug_overlay) debug_overlay->draw(gc);
    }

    void App::handle_mouse_move(glm::ivec2 rel)
    {
        if (pawn)
        {
            auto crel = glm::vec2(rel) * mouse_accel;
            if (invert_mouse)
            {
                crel.y = -crel.y;
            }
            pawn->add_look_input(-crel);
        }
    }

    void App::handle_mouse_button_down(glm::uvec2& pos, pkzo::MouseButton button)
    {
        if (screen)
        {
            auto spos = pkzo::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(pos));
            //screen->handle_mouse_button_down(spos, button);
        }
    }

    void App::handle_mouse_button_up(glm::uvec2& pos, pkzo::MouseButton button)
    {
        if (screen)
        {
            auto spos = pkzo::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(pos));
            //screen->handle_mouse_button_up(spos, button);
        }
    }

    void App::handle_key_down(pkzo::ScanCode scan)
    {
        if (scan == pkzo::ScanCode::ESCAPE)
        {
            show_main_menu();
        }
        if (pawn)
        {
            if (scan == fore_key)
            {
                pawn->add_move_input(glm::vec3(1.0, 0.0, 0.0));
            }
            if (scan == back_key)
            {
                pawn->add_move_input(glm::vec3(-1.0, 0.0, 0.0));
            }
            if (scan == left_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 1.0, 0.0));
            }
            if (scan == right_key)
            {
                pawn->add_move_input(glm::vec3(0.0, -1.0, 0.0));
            }
            if (scan == up_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 0.0, 1.0));
            }
            if (scan == down_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 0.0, -1.0));
            }
        }
    }

    void App::handle_key_up(pkzo::ScanCode scan)
    {
        if (pawn)
        {
            if (scan == fore_key)
            {
                pawn->add_move_input(glm::vec3(-1.0, 0.0, 0.0));
            }
            if (scan == back_key)
            {
                pawn->add_move_input(glm::vec3(1.0, 0.0, 0.0));
            }
            if (scan == left_key)
            {
                pawn->add_move_input(glm::vec3(0.0, -1.0, 0.0));
            }
            if (scan == right_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 1.0, 0.0));
            }
            if (scan == up_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 0.0, -1.0));
            }
            if (scan == down_key)
            {
                pawn->add_move_input(glm::vec3(0.0, 0.0, 1.0));
            }
        }
    }
}