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

#pragma once

#include <pkzo/pkzo.h>
#include <pkzo/Settings.h>

#include "Simulation.h"

namespace pong2d
{
    enum class GameState
    {
        INITIAL,
        MAIN_MENU,
        OPTIONS_MENU,
        PLAY,
        QUIT
    };

    class Game
    {
    public:
        Game(int argc, char* argv[]);
        ~Game();

        pkzo::Settings& get_settings() noexcept;

        pkzo::Window& get_window() noexcept;

        void change_state(GameState next_state) noexcept;
        GameState get_state() const noexcept;

        void capture_key(const std::function<void (pkzo::KeyMod&, pkzo::Key&)>& cb);

        int run();

    private:
        GameState state      = GameState::INITIAL;
        GameState next_state = GameState::MAIN_MENU;

        pkzo::Main     main;
        pkzo::Settings settings;

        std::unique_ptr<Simulation> simulation;

        std::unique_ptr<pkzo::Screen> screen;

        std::function<void (pkzo::KeyMod&, pkzo::Key&)> key_capture_cb;

        void tick(std::chrono::milliseconds dt);
        void update_state();
    };
}
