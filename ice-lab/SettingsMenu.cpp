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
#include "SettingsMenu.h"
#include "LabEngine.h"

namespace lab
{
    SettingsMenu::SettingsMenu(LabEngine& engine, const glm::uvec2 size)
    : ice::Screen(size)
    {
        auto style = engine.load_asset<ice::ui::Style>("ui/LightBlue.json");
        assert(style);

        auto bacground = std::make_shared<ice::Rectangle>(glm::mat3(1.0f), size, style->get_color("Screen", "background_color"));
        add_node(bacground);

        auto top_layout = std::make_shared<ice::ui::VerticalLayout>(25.0f);

        auto title_pos = glm::vec2(0.0f, static_cast<float>(size.y) * 0.4f);
        auto title_label = std::make_shared<ice::ui::Label>(title_pos, style, ice::ui::TextStyle::HEADING1, "Settings");
        top_layout->add_node(title_label);

        auto settings_matrix = std::make_shared<ice::ui::TableLayout>(2, 5.0f);

        settings_matrix->add_node(std::make_shared<ice::ui::Label>(style, "Resolution"));
        settings_matrix->add_node(std::make_shared<ice::ui::Label>(style, "<Resolution>"));

        settings_matrix->add_node(std::make_shared<ice::ui::Label>(style, "Fullscreen"));
        fullscreen_value = std::make_shared<ice::ui::CheckBox>(style, true, "ON");
        settings_matrix->add_node(fullscreen_value);

        settings_matrix->add_node(std::make_shared<ice::ui::Label>(style, "V-Sync"));
        vsync_value = std::make_shared<ice::ui::CheckBox>(style, false, "ON");
        settings_matrix->add_node(vsync_value);

        top_layout->add_node(settings_matrix);

        auto buttons_layout = std::make_shared<ice::ui::HorizontalLayout>();

        auto back_button = std::make_shared<ice::ui::Button>(style, "Back");
        back_button->on_click([&engine] () {
            engine.queue_state(EngineState::MAIN_MENU);
        });
        buttons_layout->add_node(back_button);

        auto apply_button = std::make_shared<ice::ui::Button>(style, "Apply");
        apply_button->on_click([&engine] () {
            engine.queue_state(EngineState::MAIN_MENU);
        });
        buttons_layout->add_node(apply_button);

        top_layout->add_node(buttons_layout);
        add_node(top_layout);
    }
}
