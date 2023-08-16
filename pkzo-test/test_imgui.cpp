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

#include <pkzo-imgui/Interface.h>

#include <thread>
#include <chrono>

#include <imgui.h>

#include <pkzo/EventRouter.h>
#include <pkzo/Window.h>
#include <pkzo/Mouse.h>

#include <gtest/gtest.h>
#include "pkzo_test.h"

using namespace std::chrono_literals;

TEST(Imgui, GRAPH_render_demo_window)
{
    auto router = pkzo::EventRouter{};
    auto window = pkzo::Window{router, {1600,900}, "Test"};

    auto interface = pkzo::imgui::Interface{};

    interface.add_window("About", "Demo Window", "", [&] (bool& visible) {
        ImGui::SetCurrentContext(interface.get_context());
        ImGui::ShowDemoWindow(&visible);
    });

    window.get_draw_signal().connect([&] () {
        interface.draw(window.get_size(), window.get_drawable_size());
    });

    auto mouse = pkzo::Mouse{router};
    mouse.get_button_press_signal().connect(rsig::mem_fun(&interface, &pkzo::imgui::Interface::handle_mouse_button_down));
    mouse.get_button_release_signal().connect(rsig::mem_fun(&interface, &pkzo::imgui::Interface::handle_mouse_button_up));

    router.inject_mouse_move({32, 6}, {0,0});
    router.route_events();
    window.draw();
    router.inject_mouse_button_press(pkzo::MouseButton::LEFT, {32, 6});
    router.route_events();
    window.draw();

    router.inject_mouse_button_release(pkzo::MouseButton::LEFT, {32, 6});
    router.route_events();
    window.draw();
    std::this_thread::sleep_for(1s);
    window.draw();

    router.inject_mouse_move({74,33}, {0,0});
    router.route_events();
    window.draw();
    router.inject_mouse_button_press(pkzo::MouseButton::LEFT, {32,33});
    router.route_events();
    window.draw();

    router.inject_mouse_button_release(pkzo::MouseButton::LEFT, {32,33});
    router.route_events();
    window.draw();
    std::this_thread::sleep_for(1s);
    window.draw();

    window.draw();
    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.save_screen());
}
