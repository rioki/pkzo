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

#include "MainMenu.h"
#include "OptionsMenu.h"

namespace pong2d
{
    Game::Game(int argc, char* argv[])
    {
        main.on_tick([this] () {
            tick();
        });
        main.on_quit([this] () {
            change_state(GameState::QUIT);
        });

        auto& window = main.open_window({1600, 900}, pkzo::WindowMode::STATIC, "Pkzo - Pong 2D");
        window.on_draw([this] () {
            if (screen)
            {
                screen->draw(*screen_renderer);
            }
        });

        auto& mouse = main.get_mouse();
        mouse.on_button_down([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = pkzo2d::map_to_screen(window.get_size(), screen->get_size(), pos);
                screen->handle_mouse_button_down(button, p);
            }
        });
        mouse.on_button_up([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = pkzo2d::map_to_screen(window.get_size(), screen->get_size(), pos);
                screen->handle_mouse_button_up(button, p);
            }
        });

        screen_renderer = std::make_unique<pkzo2d::ScreenRenderer>();
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

    int Game::run()
    {
        main.run();
        return 0;
    }

    void Game::tick()
    {
        if (next_state != state)
        {
            update_state();
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
            case GameState::QUIT:
                screen = nullptr;
                main.stop();
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

