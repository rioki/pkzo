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

namespace lab
{
    float grid_round(float value)
    {
        //return std::round(value) + 0.5f;
        return value;
    }

    MainMenu::MainMenu(ice::Engine& engine, const glm::uvec2 size)
    : ice::Screen(size)
    {
        auto screen_background_color   = ice::rgba(0xffffffff);
        auto button_padding            = 10.0f;
        auto button_size               = glm::vec2(150, 36);
        auto button_text_color         = ice::rgba(0x000000ff);
        auto button_font               = engine.load_asset<ice::Font>("fonts/DejaVuSans.ttf", 16);
        auto button_background_color   = ice::rgba(0x349eebff);
        auto button_background_texture = std::shared_ptr<ice::Texture>();

        auto bacground = std::make_shared<ice::Rectangle>(glm::mat3(1.0f), size, screen_background_color);
        add_node(bacground);

        // TODO: Layout
        auto position = glm::mat3(1.0f);
        position = glm::translate(position, glm::vec2(grid_round(static_cast<float>(size.x) * 0.125f), 0.5f));

        auto new_world_button = std::make_shared<ice::ui::Button>(position, button_size, "New World", button_font, button_text_color, button_background_texture, button_background_color);
        add_node(new_world_button);

        position = glm::translate(position, glm::vec2(0.0f, - (button_size.y + button_padding)));

        auto load_world_button = std::make_shared<ice::ui::Button>(position, button_size, "Load World", button_font, button_text_color, button_background_texture, button_background_color);
        add_node(load_world_button);

        position = glm::translate(position, glm::vec2(0.0f, - (button_size.y + button_padding)));

        auto settings_button = std::make_shared<ice::ui::Button>(position, button_size, "Settings", button_font, button_text_color, button_background_texture, button_background_color);
        add_node(settings_button);

        position = glm::translate(position, glm::vec2(0.0f, - (button_size.y + button_padding)));

        auto exit_button = std::make_shared<ice::ui::Button>(position, button_size, "Exit", button_font, button_text_color, button_background_texture, button_background_color);
        exit_button->on_click([this] () {
            auto engine = get_engine();
            engine->stop();
        });
        add_node(exit_button);
    }
}
