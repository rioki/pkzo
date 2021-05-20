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
    using pkzo::position;

    MainMenu::MainMenu(Game& game)
    : Screen(glm::vec2(800, 600))
    {
        auto title_font                = std::make_shared<pkzo::Font>("../assets/fonts/KarmicArcade.ttf", 30);
        auto text_font                 = std::make_shared<pkzo::Font>("../assets/fonts/Hardpixel.ttf", 20);
        auto text_material             = pkzo::make_emissive_material(glm::vec3(1.0f));
        auto button_background_texture = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Button_Background.png");
        auto button_size               = button_background_texture->get_size();
        auto button_background         = pkzo::make_emissive_material(button_background_texture);
        auto button_text               = pkzo::make_emissive_material(glm::vec3(0.2f));

        auto title = std::make_shared<pkzo::Text>(position(0.0f, 150.0f), "pkzo's Pong Demo", title_font, text_material);
        add_node(title);

        auto new_game_button = std::make_shared<pkzo::Button>(position(200.0f, -25.0f), "New Game", button_size, button_background, button_text, text_font);
        new_game_button->on_click([&game] () {
            game.change_state(GameState::PLAY);
        });
        add_node(new_game_button);

        auto options_button = std::make_shared<pkzo::Button>(position(200.0f, -100.0f), "Options", button_size, button_background, button_text, text_font);
        options_button->on_click([&game] () {
            game.change_state(GameState::OPTIONS_MENU);
        });
        add_node(options_button);

        auto quit_button = std::make_shared<pkzo::Button>(position(200.0f, -175.0f), "Quit", button_size, button_background, button_text, text_font);
        quit_button->on_click([&game] () {
            game.change_state(GameState::QUIT);
        });
        add_node(quit_button);
    }
}
