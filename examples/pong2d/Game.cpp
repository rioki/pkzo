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

#ifdef _WIN32
#include <shlobj.h>
#include <windows.h>
#endif

#include "MainMenu.h"
#include "OptionsMenu.h"
#include "View.h"

namespace pong2d
{
    Game::Game(int argc, char* argv[])
    : engine("pong2d")
    {
        engine.on_tick([this] (auto dt) {
            tick(dt);
        });
        engine.on_quit([this] () {
            change_state(GameState::QUIT);
        });

        auto& window = engine.get_main_window();
        window.set_caption("Pkzo - Pong 2D");
        window.on_draw([this] () {
            if (screen)
            {
                screen->draw();
            }
        });

        auto& mouse = engine.get_mouse();
        mouse.on_button_down([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = pkzo::map_to_screen(window.get_size(), screen->get_size(), pos);
                //screen->handle_mouse_button_down(button, p);
            }
        });
        mouse.on_button_up([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = pkzo::map_to_screen(window.get_size(), screen->get_size(), pos);
                //screen->handle_mouse_button_up(button, p);
            }
        });
        mouse.on_move([this, &window] (auto pos, auto mov) {
            if (screen)
            {
                auto p = pkzo::map_to_screen(window.get_size(), screen->get_size(), pos);
                auto m = pkzo::map_to_screen(window.get_size(), screen->get_size(), mov);
                //screen->handle_mouse_move(p, m);
            }
        });

        auto& keyboard = engine.get_keyboard();
        keyboard.on_key_down([this] (auto mod, auto key) {
            if (!key_capture_cb)
            {
                //screen->handle_key_down(mod, key);
            }
        });
        keyboard.on_key_up([this] (auto mod, auto key) {
            if (!key_capture_cb)
            {
                //screen->handle_key_up(mod, key);
            }
            else
            {
                key_capture_cb(mod, key);
                key_capture_cb = nullptr;
            }
        });
        keyboard.on_text([this] (auto text) {
            //screen->handle_text(text);
        });
    }

    Game::~Game() = default;

    pkzo::Settings& Game::get_settings() noexcept
    {
        return engine.get_settings();
    }

    pkzo::Window& Game::get_window() noexcept
    {
        return engine.get_main_window();
    }

    void Game::change_state(GameState ns) noexcept
    {
        assert(ns != GameState::INITIAL);
        next_state = ns;
    }

    GameState Game::get_state() const noexcept
    {
        return state;
    }

    void Game::capture_key(const std::function<void(pkzo::KeyMod&, pkzo::Key&)>& cb)
    {
        key_capture_cb = cb;
    }

    int Game::run()
    {
        engine.run();
        return 0;
    }

    void Game::tick(std::chrono::milliseconds dt)
    {
        if (next_state != state)
        {
            update_state();
        }
        if (state == GameState::PLAY)
        {
            assert(simulation);
            simulation->tick(dt);
        }
        if (screen)
        {
            //screen->animate(dt);
        }
    }

    void Game::update_state()
    {
        switch (next_state)
        {
            case GameState::MAIN_MENU:
                screen = std::make_unique<MainMenu>(*this);
                break;
            case GameState::OPTIONS_MENU:
                screen = std::make_unique<OptionsMenu>(*this);
                break;
            case GameState::PLAY:
            {
                std::random_device rd;
                simulation = std::make_unique<Simulation>(rd());
                screen = std::make_unique<View>(*this, *simulation);
                break;
            }
            case GameState::QUIT:
                screen = nullptr;
                engine.stop();
                break;
            default:
                assert(false);
                break;
        }

        state = next_state;
    }
}

int main(int argc, char* argv[])
{
    pong2d::Game game(argc, argv);
    return game.run();
}

