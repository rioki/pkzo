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
#include "OptionsMenu.h"

#include "KeyInput.h"
#include "Game.h"

namespace pong2d
{
    OptionsMenu::OptionsMenu(Game& game)
    : Screen(glm::vec2(800, 600))
    {
        auto title_font           = std::make_shared<pkzo::Font>("../assets/fonts/KarmicArcade.ttf", 30);
        auto text_font            = std::make_shared<pkzo::Font>("../assets/fonts/Hardpixel.ttf", 20);
        auto label_color          = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
        auto button_background    = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Button_Background.png");
        auto button_caption_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        auto checkbox_checked     = std::make_shared<pkzo::Texture>("../assets/ui/pixels/CheckBox_Checked.png");
        auto checkbox_unchecked   = std::make_shared<pkzo::Texture>("../assets/ui/pixels/CheckBox_Unchecked.png");

        auto slider_background    = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Slider_Horizontal_200.png");
        auto slider_handle        = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Slider_Handle.png");

        auto title = std::make_shared<pkzo2d::Text>(title_font, "Options");
        title->set_position({0.0f, 250.0f});
        add_node(title);

        auto resolution_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Resolution");
        resolution_label->set_position({-390.0f + resolution_label->get_size().x / 2.0f, 150.0f});
        add_node(resolution_label);
        auto fullscren_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Fullscreen");
        fullscren_label->set_position({-390.0f + fullscren_label->get_size().x / 2.0f, 100.0f});
        add_node(fullscren_label);
        auto old_vhs_effect_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Old VHS Effect");
        old_vhs_effect_label->set_position({-390.0f + old_vhs_effect_label->get_size().x / 2.0f, 50.0f});
        add_node(old_vhs_effect_label);

        auto fullscreen_value = std::make_shared<pkzoui::CheckBox>(checkbox_checked, checkbox_unchecked);
        fullscreen_value->set_position({-10.0f - fullscreen_value->get_size().x / 2.0f, 100.0f});
        add_node(fullscreen_value);
        auto old_vhs_effect_value = std::make_shared<pkzoui::CheckBox>(checkbox_checked, checkbox_unchecked);
        old_vhs_effect_value->set_position({-10.0f - fullscreen_value->get_size().x / 2.0f, 50.0f});
        add_node(old_vhs_effect_value);

        auto music_volume_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Music Volume");
        music_volume_label->set_position({-390.0f + music_volume_label->get_size().x / 2.0f, -50.0f});
        add_node(music_volume_label);
        auto sfx_volume_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "SFX Volume");
        sfx_volume_label->set_position({-390.0f + sfx_volume_label->get_size().x / 2.0f, -100.0f});
        add_node(sfx_volume_label);

        auto music_volume_value = std::make_shared<pkzoui::Slider>(slider_background, slider_handle);
        music_volume_value->set_position({-10.0f - music_volume_value->get_size().x / 2.0f, -50.0f});
        add_node(music_volume_value);
        auto sfx_volume_value = std::make_shared<pkzoui::Slider>(slider_background, slider_handle);
        sfx_volume_value->set_position({-10.0f - sfx_volume_value->get_size().x / 2.0f, -100.0f});
        add_node(sfx_volume_value);

        auto p1_up_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Player 1 Up");
        p1_up_label->set_position({10.0f + p1_up_label->get_size().x / 2.0f, 150.0f});
        add_node(p1_up_label);
        auto p1_down_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Player 1 Down");
        p1_down_label->set_position({10.0f + p1_down_label->get_size().x / 2.0f, 100.0f});
        add_node(p1_down_label);
        auto p2_up_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Player 2 Up");
        p2_up_label->set_position({10.0f + p2_up_label->get_size().x / 2.0f, 50.0f});
        add_node(p2_up_label);
        auto p2_down_label = std::make_shared<pkzo2d::Text>(text_font, label_color, "Player 2 Down");
        p2_down_label->set_position({10.0f + p2_down_label->get_size().x / 2.0f, 0.0f});
        add_node(p2_down_label);

        auto p1_up_value = std::make_shared<KeyInput>(text_font, pkzo::Key::Q);
        p1_up_value->set_position({250.0f, 150.0f});
        p1_up_value->on_click([&game, p1_up_value] () {
            game.capture_key([p1_up_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p1_up_value->set_key(key);
                }
            });
        });
        add_node(p1_up_value);

        auto p1_down_value = std::make_shared<KeyInput>(text_font, pkzo::Key::A);
        p1_down_value->set_position({250.0f, 100.0f});
        p1_down_value->on_click([&game, p1_down_value] () {
            game.capture_key([p1_down_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p1_down_value->set_key(key);
                }
            });
        });
        add_node(p1_down_value);

        auto p2_up_value = std::make_shared<KeyInput>(text_font, pkzo::Key::P);
        p2_up_value->set_position({250.0f, 50.0f});
        p2_up_value->on_click([&game, p2_up_value] () {
            game.capture_key([p2_up_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p2_up_value->set_key(key);
                }
            });
        });
        add_node(p2_up_value);

        auto p2_down_value = std::make_shared<KeyInput>(text_font, pkzo::Key::L);
        p2_down_value->set_position({250.0f, 0.0f});
        p2_down_value->on_click([&game, p2_down_value] () {
            game.capture_key([p2_down_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p2_down_value->set_key(key);
                }
            });
        });
        add_node(p2_down_value);

        auto back_button = std::make_shared<pkzoui::Button>(button_background, text_font, button_caption_color, "Back");
        back_button->set_position({165.0f, -270.0f});
        back_button->on_click([&game] () {
            game.change_state(GameState::MAIN_MENU);
        });
        add_node(back_button);

        auto apply_button = std::make_shared<pkzoui::Button>(button_background, text_font, button_caption_color, "Apply");
        apply_button->set_position({320.0f, -270.0f});
        apply_button->on_click([&game] () {
            game.change_state(GameState::MAIN_MENU);
        });
        add_node(apply_button);
    }
}
