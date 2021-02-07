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

#include "pch.h"
#include "MainMenu.h"

#include "Game.h"

namespace pong2d
{
    MainMenu::MainMenu(Game& game)
    : Screen(glm::vec2(800, 600))
    {
        auto title_font = std::make_shared<pkzo::Font>("../assets/fonts/KarmicArcade.ttf", 30);
        auto text_font = std::make_shared<pkzo::Font>("../assets/fonts/Hardpixel.ttf", 20);
        auto button_background = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Button_Background.png");
        auto button_caption_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

        auto title = std::make_shared<pkzo2d::Text>(title_font, "pkzo's Pong Demo");
        title->set_position({0.0f, 150.0f});
        add_node(title);

        auto new_game_button = std::make_shared<pkzoui::Button>(button_background, text_font, button_caption_color, "New Game");
        new_game_button->set_position({200.0f, -25.0f});
        new_game_button->on_click([&game] () {
            // TODO
        });
        add_node(new_game_button);

        auto options_button = std::make_shared<pkzoui::Button>(button_background, text_font, button_caption_color, "Options");
        options_button->set_position({200.0f, -100.0f});
        options_button->on_click([&game] () {
            game.change_state(GameState::OPTIONS_MENU);
        });
        add_node(options_button);

        auto quit_button = std::make_shared<pkzoui::Button>(button_background, text_font, button_caption_color, "Quit");
        quit_button->set_position({200.0f, -175.0f});
        quit_button->on_click([&game] () {
            game.change_state(GameState::QUIT);
        });
        add_node(quit_button);
    }
}
