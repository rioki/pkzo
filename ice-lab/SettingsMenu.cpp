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
        auto screen_background_color   = ice::rgba(0xffffffff);
        auto button_padding            = 10.0f;
        auto button_size               = glm::vec2(150, 36);
        auto button_text_color         = ice::rgba(0x000000ff);
        auto button_font               = engine.load_asset<ice::Font>("fonts/DejaVuSans.ttf", 16);
        auto title_font                = engine.load_asset<ice::Font>("fonts/DejaVuSans.ttf", 32);
        auto button_background_color   = ice::rgba(0x349eebff);
        auto button_background_texture = std::shared_ptr<ice::Texture>();

        auto bacground = std::make_shared<ice::Rectangle>(glm::mat3(1.0f), size, screen_background_color);
        add_node(bacground);

        auto title_pos = glm::translate(glm::mat3(1.0f), glm::vec2(0.0f, static_cast<float>(size.y) * 0.4f));
        auto title_label = std::make_shared<ice::ui::Label>(title_pos, "Settings", title_font, button_text_color);
        add_node(title_label);

        auto position = glm::mat3(1.0f);
        position = glm::translate(position, glm::vec2(static_cast<float>(size.x) * 0.3f, -static_cast<float>(size.y) * 0.3f));

        auto back_button = std::make_shared<ice::ui::Button>(position, button_size, "Back", button_font, button_text_color, button_background_texture, button_background_color);
        back_button->on_click([&engine] () {
            engine.queue_state(EngineState::MAIN_MENU);
        });
        add_node(back_button);

        position = glm::translate(position, glm::vec2(200.0f, 0.0f));
        auto apply_button = std::make_shared<ice::ui::Button>(position, button_size, "Apply", button_font, button_text_color, button_background_texture, button_background_color);
        apply_button->on_click([&engine] () {
            engine.queue_state(EngineState::MAIN_MENU);
        });
        add_node(apply_button);
    }
}
