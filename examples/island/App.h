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

#pragma once

#include <pkzo/pkzo.h>
#include <pkzo2d/pkzo2d.h>
#include <pkzo3d/pkzo3d.h>

#include "StateMachine.h"

namespace island
{
    class Settings;
    class DebugOverlay;

    class App
    {
    public:
        App(int argc, char* argv[]);
        ~App();

        void run();

    private:
        using time_point = std::chrono::steady_clock::time_point;
        enum class State
        {
            INIT,
            MAIN_MENU,
            SETTINGS_MENU,
            PLAY,
            PAUSE_MENU,
            END,
            ERROR
        };

        using InputEvent = std::variant<pkzo::MouseMoveEvent, pkzo::MouseButtonDownEvent, pkzo::MouseButtonUpEvent, pkzo::MouseWheelEvent>;

        time_point                      last_tick = std::chrono::steady_clock::now();

        std::unique_ptr<Settings>       settings;
        std::unique_ptr<pkzo::Window>   window;
        std::unique_ptr<pkzo::Mouse>    mouse;
        std::unique_ptr<pkzo::Keyboard> keyboard;

        std::unique_ptr<pkzo2d::Screen> screen;
        std::unique_ptr<pkzo3d::Scene>  scene;
        std::unique_ptr<DebugOverlay>   debug_overlay;

        rex::StateMachine<State, InputEvent> state_machine;

        void handle_draw(pkzo::GraphicContext& gc);
    };
}

