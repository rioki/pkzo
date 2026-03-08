// Garden
// Copyright 2026 Sean Farrell
// All rights reserved.

#include "App.h"

#include <pkzo/enum_helpers.h>
#include <pkzo/glm_fkyaml.h>
#include <pkzo/debug.h>
#include <pkzo/stdng.h>

#include "env.h"
#include "Settings.h"
#include "DebugOverlay.h"
#include "MainMenu.h"
#include "SettingsMenu.h"

namespace island
{
    using fsec = std::chrono::duration<float>;

    App::App(int argc, char* argv[])
    {
        pkzo::on_quit([&] () { state_machine.queue_state(State::END);  });

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

        mouse = std::make_unique<pkzo::Mouse>();
        mouse->on_move([this] (auto event)         { state_machine.send_event(event); });
        mouse->on_button_down([this] (auto event)  { state_machine.send_event(event); });
        mouse->on_button_up([this] (auto event)    { state_machine.send_event(event); });
        mouse->on_wheel([this] (auto event)        { state_machine.send_event(event); });

        keyboard = std::make_unique<pkzo::Keyboard>();
        //keyboard->on_key_down([this] (auto event) { state_machine.send_event(event); } );
       // keyboard->on_key_up([this] (auto event)   { state_machine.send_event(event); } );

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
                .start_action    = [this] () { state_machine.queue_state(State::PLAY);          },
                .settings_action = [this] () { state_machine.queue_state(State::SETTINGS_MENU); },
                .exit_action     = [this] () { state_machine.queue_state(State::END);           },
            });
        });
        state_machine.on_tick(State::MAIN_MENU, [this] (float dt) {
            screen->update(dt);
        });
        state_machine.on_event(State::MAIN_MENU, [this] (auto event) {
            std::visit(stdng::loose_overloaded(
                [this](pkzo::MouseButtonDownEvent ev)      {
                    auto spos = pkzo2d::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(ev.position));
                    screen->handle_mouse_button_down(spos, ev.button);
                },
                [this](pkzo::MouseButtonUpEvent ev)        {
                    auto spos = pkzo2d::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(ev.position));
                    screen->handle_mouse_button_up(spos, ev.button);
                }
            ), event);
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
            std::visit(stdng::loose_overloaded(
                [this](pkzo::MouseButtonDownEvent ev)      {
                    auto spos = pkzo2d::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(ev.position));
                    screen->handle_mouse_button_down(spos, ev.button);
                },
                [this](pkzo::MouseButtonUpEvent ev)        {
                    auto spos = pkzo2d::map_to_screen(window->get_resolution(), screen->get_size(), glm::vec2(ev.position));
                    screen->handle_mouse_button_up(spos, ev.button);
                }
            ), event);
        });
        state_machine.on_exit(State::SETTINGS_MENU, [this] () {
            screen = nullptr;
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

            pkzo::rotue_events();
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

