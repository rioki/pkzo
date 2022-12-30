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
        auto style = engine.load_asset<ice::ui::Style>("ui/DarkBlue.json");
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

        auto open_editor_button = std::make_shared<ice::ui::Button>(style, "Open Editor");
        open_editor_button->on_click([&engine] () {
            engine.queue_state(EngineState::EDITOR);
        });
        layout->add_node(open_editor_button);

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

        // TEST place to test right click menu
        auto hit_area = std::make_shared<ice::HitArea>(glm::mat4(1.0f), size);
        hit_area->on_mouse_down([this, style, &engine] (auto inside, auto button, auto pos) {
            if (inside && button == ice::MouseButton::RIGHT)
            {
                if (popup_menu)
                {
                    popup_menu->set_position(pos);
                }
                else
                {
                    popup_menu = std::make_shared<ice::ui::Menu>(pos, style);
                    popup_menu->add_item("Play", c9y::sync_fun([this, &engine] () {
                        this->remove_node(popup_menu);
                        engine.queue_state(EngineState::PLAY);
                    }));
                    popup_menu->add_item("Do Nothing", c9y::sync_fun([this, &engine] () {
                        this->remove_node(popup_menu);
                    }));
                    popup_menu->add_item("Settings", c9y::sync_fun([this, &engine] () {
                        this->remove_node(popup_menu);
                        engine.queue_state(EngineState::SETTINGS_MENU);
                    }));
                    popup_menu->add_item("Exit", c9y::sync_fun([this, &engine] () {
                        this->remove_node(popup_menu);
                        engine.queue_state(EngineState::END);
                    }));
                    add_node(popup_menu);
                }
            }
        });
        add_node(hit_area);

        // TEST
    }
}
