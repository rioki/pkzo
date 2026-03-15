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

#include <memory>

#include <pkzo/pkzo.h>
#include <pkzo3d/pkzo3d.h>

namespace lab
{
    class DebugOverlay;
    class Pawn;

    constexpr auto VERSION = "0.1.0";

    class App
    {
    public:
        App(int argc, char* argv[]);
        ~App();

        void show_main_menu();
        void start_material_test();
        void start_physics_test();

        int run();
        void stop();


    private:
        using time_point = std::chrono::steady_clock::time_point;

        bool running = false;
        time_point last_tick = std::chrono::steady_clock::now();

        std::unique_ptr<pkzo::Window>   window;
        std::unique_ptr<pkzo::Mouse>    mouse;
        std::unique_ptr<pkzo::Keyboard> keyboard;

        std::unique_ptr<pkzo::Screen>                screen;
        std::optional<std::unique_ptr<pkzo::Screen>> next_screen;
        std::unique_ptr<pkzo3d::Scene>                 scene;
        std::optional<std::unique_ptr<pkzo3d::Scene>>  next_scene;
        Pawn*                                          pawn = nullptr;
        std::unique_ptr<DebugOverlay>                  debug_overlay;

        // settings
        pkzo::ScanCode fore_key  = pkzo::ScanCode::W;
        pkzo::ScanCode back_key  = pkzo::ScanCode::S;
        pkzo::ScanCode left_key  = pkzo::ScanCode::A;
        pkzo::ScanCode right_key = pkzo::ScanCode::D;
        pkzo::ScanCode up_key    = pkzo::ScanCode::SPACE;
        pkzo::ScanCode down_key  = pkzo::ScanCode::LCTRL;
        float          mouse_accel = 0.25f;
        bool           invert_mouse = true;

        void tick();

        void handle_draw(pkzo::GraphicContext& gc);
        void handle_mouse_move(glm::ivec2 rel);
        void handle_mouse_button_down(glm::uvec2& pos, pkzo::MouseButton button);
        void handle_mouse_button_up(glm::uvec2& pos, pkzo::MouseButton button);;
        void handle_key_down(pkzo::ScanCode scan);
        void handle_key_up(pkzo::ScanCode scan);

        App(const App& rhs) = delete;
        App& operator = (const App& rhs) = delete;
    };
}