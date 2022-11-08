// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "MainMenu.h"
#include "LabEngine.h"

namespace lab
{
    MainMenu::MainMenu(LabEngine& engine, const glm::uvec2 size)
    : ice::Screen(size)
    {
        auto style = engine.load_asset<ice::ui::Style>("ui/LightBlue.json");
        assert(style);

        // Background
        // TODO screen background as a property of screen?
        add_node(std::make_shared<ice::Rectangle>(glm::mat3(1.0f), size, style->get_color("Screen", "background_color")));

        auto layout = std::make_shared<ice::ui::VerticalLayout>(glm::vec2(static_cast<float>(size.x) * 0.125f, 0.5f));

        auto new_world_button = std::make_shared<ice::ui::Button>(style, "New World");
        new_world_button->on_click([&engine] () {
            engine.queue_state(EngineState::PLAY);
        });
        layout->add_node(new_world_button);

        auto load_world_button = std::make_shared<ice::ui::Button>(style, "Load World");
        load_world_button->on_click([&engine] () {
            engine.queue_state(EngineState::PLAY);
        });
        layout->add_node(load_world_button);

        auto settings_button = std::make_shared<ice::ui::Button>(style, "Settings");
        settings_button->on_click([&engine] () {
            engine.queue_state(EngineState::SETTINGS_MENU);
        });
        layout->add_node(settings_button);

        auto exit_button = std::make_shared<ice::ui::Button>(style, "Exit");
        exit_button->on_click([&engine] () {
            engine.queue_state(EngineState::END);
        });
        layout->add_node(exit_button);

        add_node(layout);
    }
}
