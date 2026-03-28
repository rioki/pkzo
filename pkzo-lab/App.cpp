// Garden
// Copyright 2026 Sean Farrell
// All rights reserved.

#include "App.h"

#include <pkzo/enum_helpers.h>
#include <pkzo/glm_fkyaml.h>
#include <pkzo/debug.h>
#include <pkzo/stdng.h>
#include <tinyformat.h>

#include "env.h"
#include "Settings.h"
#include "DebugOverlay.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "Pawn.h"
#include "MaterialTestScene.h"
#include "PhysicsTestScene.h"

namespace lab
{
    using fsec = std::chrono::duration<float>;

    pkzo::InputEvent map_to_screen(const pkzo::Window& window, pkzo::Screen& screen, const pkzo::InputEvent& event)
    {
        return std::visit(stdng::overloaded{
            [&](pkzo::MouseButtonDownEvent e) -> pkzo::InputEvent {
                e.position = pkzo::map_to_screen(window.get_resolution(), screen.get_size(), glm::vec2(e.position));
                return e;
            },
            [&](pkzo::MouseButtonUpEvent e) -> pkzo::InputEvent {
                e.position = pkzo::map_to_screen(window.get_resolution(), screen.get_size(), glm::vec2(e.position));
                return e;
            },
            [](auto e) -> pkzo::InputEvent {
                return e;
            }
        }, event);
    }

    App::App(int argc, char* argv[])
    {
        pkzo::on_quit([this] () { state_machine.queue_state(State::END); });
        pkzo::on_input([this] (auto event) { state_machine.send_event(event); });

        settings = std::make_unique<Settings>();
        auto settings_file = get_user_folder() / "settings.yml";
        if (std::filesystem::exists(settings_file))
        {
            settings->load(settings_file);
        }

        window = std::make_unique<pkzo::Window>(pkzo::Window::Init{
            .title = "pkzo Island Demo",
            .size  = settings->get("Window", "size", glm::uvec2(800u, 600u)),
            .state = settings->get("Window", "fullscreen", false) ? pkzo::WindowState::FULLSCREEN : pkzo::WindowState::WINDOW,
        });
        window->on_draw([this] (auto& gc) { handle_draw(gc); });

        if (settings->get("Debug", "overlay", false) || pkzo::is_debugger_present())
        {
            debug_overlay = std::make_unique<DebugOverlay>(DebugOverlay::Init{
                .size = glm::vec2(window->get_resolution())
            });
        }

        // Main Menu State
        state_machine.on_enter(State::MAIN_MENU, [this] () {
            screen = std::make_unique<MainMenu>(MainMenu::Init{
                .size            = glm::vec2(window->get_resolution()),
                .start_action    = [this] (const std::string& id) { state_machine.queue_state(State::PLAY, id); },
                .settings_action = [this] ()                      { state_machine.queue_state(State::SETTINGS_MENU); },
                .exit_action     = [this] ()                      { state_machine.queue_state(State::END);           },
            });
        });
        state_machine.on_tick(State::MAIN_MENU, [this] (float dt) {
            screen->update(dt);
        });
        state_machine.on_event(State::MAIN_MENU, [this] (auto event) {
            const auto ev = map_to_screen(*window, *screen, event);
            screen->handle_input(ev);
        });
        state_machine.on_exit(State::MAIN_MENU, [this] () {
            screen = nullptr;
        });

        // Settings Menu State
        state_machine.on_enter(State::SETTINGS_MENU, [this] () {
            screen = std::make_unique<SettingsMenu>(SettingsMenu::Init{
                .size            = glm::vec2(window->get_resolution()),
                .back_action     = [this] () { state_machine.queue_state(State::MAIN_MENU); }
            });
        });
        state_machine.on_tick(State::SETTINGS_MENU, [this] (float dt) {
            screen->update(dt);
        });
        state_machine.on_event(State::SETTINGS_MENU, [this] (auto event) {
            const auto ev = map_to_screen(*window, *screen, event);
            screen->handle_input(ev);
        });
        state_machine.on_exit(State::SETTINGS_MENU, [this] () {
            screen = nullptr;
        });

        // Play
        state_machine.on_enter(State::PLAY, [this] (const auto& id) {
            if (std::any_cast<std::string>(id) == "materials")
            {
                scene = std::make_unique<MaterialTestScene>();
            }
            else if (std::any_cast<std::string>(id) == "physics")
            {
                scene = std::make_unique<PhysicsTestScene>();
            }
            else
            {
                pkzo::trace(tfm::format("Unknown scene %s", std::any_cast<std::string>(id)));
                state_machine.queue_state(State::MAIN_MENU);
                return;
            }
            pawn = scene->add<Pawn>({
                .fore_key     = settings->get("Pawn", "fore_key",     pkzo::ScanCode::W),
                .back_key     = settings->get("Pawn", "back_key",     pkzo::ScanCode::S),
                .left_key     = settings->get("Pawn", "left_key",     pkzo::ScanCode::A),
                .right_key    = settings->get("Pawn", "right_key",    pkzo::ScanCode::D),
                .up_key       = settings->get("Pawn", "up_key",       pkzo::ScanCode::SPACE),
                .down_key     = settings->get("Pawn", "down_key",     pkzo::ScanCode::LCTRL),
                .mouse_accel  = settings->get("Pawn", "mouse_accel",  0.25f),
                .invert_mouse = settings->get("Pawn", "invert_mouse", true),
            });
        });
        state_machine.on_tick(State::PLAY, [this] (float dt) {
            scene->update(dt);
        });
        state_machine.on_event(State::PLAY, [this] (auto event) {
            pawn->handle_input(event);
        });
        state_machine.on_exit(State::PLAY, [this] () {
            scene = nullptr;
            pawn  = nullptr;
        });

        state_machine.queue_state(State::MAIN_MENU);
    }

    App::~App()
    {
        window = nullptr;
    }

    void App::run()
    {
        while (pkzo::none_of(state_machine.get_state(), {State::END, State::ERROR}))
        {
            auto now = std::chrono::steady_clock::now();
            auto dt  = std::chrono::duration_cast<fsec>(now - last_tick).count();
            last_tick = now;

            pkzo::route_events();
            state_machine.tick(dt); // screen & sceen are updated inside the state_machine
            if (debug_overlay) debug_overlay->update(dt);
            window->draw();
        }
    }

    void App::handle_draw(pkzo::GraphicContext& gc)
    {
        if (scene)         scene->draw(gc);
        if (screen)        screen->draw(gc);
        if (debug_overlay) debug_overlay->draw(gc);
    }
}
