// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "Application.h"

#include <imgui.h>

namespace lab
{
    Application::Application()
    {
        // TODO settings

        event_router.get_quit_signal().connect([this] () {
            stop();
        });

        window.get_draw_signal().connect([this] () {
            debug_interface.draw(window.get_size(), window.get_drawable_size());
        });

        mouse.get_button_press_signal().connect([this] (auto button, auto pos) {
            pkzo::trace(std::format("{},{}", pos.x, pos.y));
            debug_interface.handle_mouse_button_down(button, pos);
        });
        mouse.get_button_release_signal().connect([this] (auto button, auto pos) {
            debug_interface.handle_mouse_button_up(button, pos);
        });
        mouse.get_move_signal().connect([this] (auto pos, auto rel) {
            debug_interface.handle_mouse_move(pos, rel);
        });
        mouse.get_wheel_signal().connect([this] (auto rel) {
            debug_interface.handle_mouse_wheel(rel);
        });

        keyboard.get_key_press_signal().connect([this] (auto mod, auto key) {
            debug_interface.handle_keboard_down(mod, key);
        });
        keyboard.get_key_release_signal().connect([this] (auto mod, auto key) {
            debug_interface.handle_keboard_up(mod, key);
        });
        keyboard.get_text_signal().connect([this] (auto text) {
            debug_interface.handle_keboard_text(text);
        });

        debug_interface.add_menu_action("File", "Exit", "ALT+F4", [this] () {
            stop();
        });

        debug_interface.add_window("Help", "Show ImGui Demo Window", "", [this] (bool& visible) {
            ImGui::SetCurrentContext(debug_interface.get_context());
            ImGui::ShowDemoWindow(&visible);
        });

        debug_interface.add_window("Help", "About Pkzo Lab", "", [this] (bool& visible) {
            ImGui::SetCurrentContext(debug_interface.get_context());
            ImGui::Begin("About Pkzo Lab", &visible);
            ImGui::Text("Pkzo Lab is a small tech sample used to develop and test pkzo.");
            if (ImGui::Button("Close"))
            {
                visible = false;
            }
            ImGui::End();
        });
    }

    int Application::run()
    {
        running = true;
        while (running)
        {
            tick();
        }
        return 0;
    }

    void Application::stop()
    {
        running = false;
    }

    void Application::tick()
    {
        event_router.route_events();
        window.draw();
    }
}
