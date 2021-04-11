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
#include "Settings.h"

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

        auto dropdown_background  = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Dropdown_200_Background.png");
        auto dropdown_button      = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Dropdown_Button.png");
        auto menu_top             = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Top.png");
        auto menu_body            = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Body.png");
        auto menu_bottom          = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Bottom.png");
        auto menu_text_color      = glm::vec4(0.0, 0.0, 0.0, 1.0);

        auto& settings = game.get_settings();

        auto title = std::make_shared<pkzo::two::Text>(title_font, "Options");
        title->set_position({0.0f, 250.0f});
        add_node(title);

        auto resolution_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Resolution");
        resolution_label->set_position({-390.0f + resolution_label->get_size().x / 2.0f, 150.0f});
        add_node(resolution_label);
        auto fullscren_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Fullscreen");
        fullscren_label->set_position({-390.0f + fullscren_label->get_size().x / 2.0f, 100.0f});
        add_node(fullscren_label);
        auto old_tv_effect_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Old TV Effect");
        old_tv_effect_label->set_position({-390.0f + old_tv_effect_label->get_size().x / 2.0f, 50.0f});
        add_node(old_tv_effect_label);

        auto resolutions = pkzo::Window::get_valid_reslutions(0);
        std::vector<std::string> resolution_text(resolutions.size());
        std::transform(begin(resolutions), end(resolutions), begin(resolution_text), [] (auto res) {
            std::stringstream buff;
            buff << res.x << "x" << res.y;
            return buff.str();
        });
        auto width = settings.get_value("Video", "width", 800u);
        auto height = settings.get_value("Video", "height", 600u);
        auto index = std::distance(begin(resolutions), std::find(begin(resolutions), end(resolutions), glm::uvec2(width, height)));
        auto resolution_value = std::make_shared<pkzo::two::ui::DropDownMenu>(dropdown_background, dropdown_button, menu_top, menu_body, menu_bottom, text_font, menu_text_color);
        resolution_value->set_options(resolution_text);
        resolution_value->set_selected_option(index);
        resolution_value->set_position({-10.0f - resolution_value->get_size().x / 2.0f, 150.0f});
        add_node(resolution_value);

        auto fullscreen_value = std::make_shared<pkzo::two::ui::CheckBox>(checkbox_checked, checkbox_unchecked);
        fullscreen_value->set_position({-10.0f - fullscreen_value->get_size().x / 2.0f, 100.0f});
        fullscreen_value->set_checked(settings.get_value("Video", "fullscreen", false));
        add_node(fullscreen_value);
        auto old_tv_effect_value = std::make_shared<pkzo::two::ui::CheckBox>(checkbox_checked, checkbox_unchecked);
        old_tv_effect_value->set_position({-10.0f - fullscreen_value->get_size().x / 2.0f, 50.0f});
        old_tv_effect_value->set_checked(settings.get_value("Video", "old_tv_effect", true));
        add_node(old_tv_effect_value);

        auto music_volume_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Music Volume");
        music_volume_label->set_position({-390.0f + music_volume_label->get_size().x / 2.0f, -50.0f});
        add_node(music_volume_label);
        auto sfx_volume_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "SFX Volume");
        sfx_volume_label->set_position({-390.0f + sfx_volume_label->get_size().x / 2.0f, -100.0f});
        add_node(sfx_volume_label);

        auto music_volume_value = std::make_shared<pkzo::two::ui::Slider>(slider_background, slider_handle);
        music_volume_value->set_position({-10.0f - music_volume_value->get_size().x / 2.0f, -50.0f});
        music_volume_value->set_value(settings.get_value("Sound", "music_volume", 0.7f));
        add_node(music_volume_value);
        auto sfx_volume_value = std::make_shared<pkzo::two::ui::Slider>(slider_background, slider_handle);
        sfx_volume_value->set_position({-10.0f - sfx_volume_value->get_size().x / 2.0f, -100.0f});
        sfx_volume_value->set_value(settings.get_value("Sound", "sfx_volume", 0.7f));
        add_node(sfx_volume_value);

        auto p1_up_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Player 1 Up");
        p1_up_label->set_position({10.0f + p1_up_label->get_size().x / 2.0f, 150.0f});
        add_node(p1_up_label);
        auto p1_down_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Player 1 Down");
        p1_down_label->set_position({10.0f + p1_down_label->get_size().x / 2.0f, 100.0f});
        add_node(p1_down_label);
        auto p2_up_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Player 2 Up");
        p2_up_label->set_position({10.0f + p2_up_label->get_size().x / 2.0f, 50.0f});
        add_node(p2_up_label);
        auto p2_down_label = std::make_shared<pkzo::two::Text>(text_font, label_color, "Player 2 Down");
        p2_down_label->set_position({10.0f + p2_down_label->get_size().x / 2.0f, 0.0f});
        add_node(p2_down_label);

        auto p1_up_value = std::make_shared<KeyInput>(text_font, settings.get_value("Player1", "up", pkzo::Key::Q));
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

        auto p1_down_value = std::make_shared<KeyInput>(text_font, settings.get_value("Player1", "down", pkzo::Key::A));
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

        auto p2_up_value = std::make_shared<KeyInput>(text_font, settings.get_value("Player2", "up", pkzo::Key::P));
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

        auto p2_down_value = std::make_shared<KeyInput>(text_font, settings.get_value("Player2", "down", pkzo::Key::L));
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

        auto back_button = std::make_shared<pkzo::two::ui::Button>(button_background, text_font, button_caption_color, "Back");
        back_button->set_position({165.0f, -270.0f});
        back_button->on_click([&game] () {
            game.change_state(GameState::MAIN_MENU);
        });
        add_node(back_button);

        auto apply_button = std::make_shared<pkzo::two::ui::Button>(button_background, text_font, button_caption_color, "Apply");
        apply_button->set_position({320.0f, -270.0f});
        apply_button->on_click([=, &game] () {
            auto& settings = game.get_settings();

            game.change_state(GameState::MAIN_MENU);

            auto res_idx = resolution_value->get_selected_option();
            assert(res_idx);
            auto res = resolutions[res_idx.value()];
            auto fullscreen = fullscreen_value->get_checked();
            auto old_tv_effect = old_tv_effect_value->get_checked();

            game.get_window().resize(res, fullscreen ? pkzo::WindowMode::FULLSCREEN : pkzo::WindowMode::STATIC);
            settings.set_value("Video", "width", res.x);
            settings.set_value("Video", "height", res.y);
            settings.set_value("Video", "fullscreen", fullscreen);
            settings.set_value("Video", "old_tv_effect", old_tv_effect);

            auto music_volume = music_volume_value->get_value();
            auto sfx_volume   = sfx_volume_value->get_value();
            settings.set_value("Sound", "music_volume", music_volume);
            settings.set_value("Sound", "sfx_volume",   sfx_volume);

            auto left_up   = p1_up_value->get_key();
            auto left_down = p1_down_value->get_key();
            auto right_up   = p2_up_value->get_key();
            auto right_down = p2_down_value->get_key();
            settings.set_value("Player1", "up", left_up);
            settings.set_value("Player1", "down", left_down);
            settings.set_value("Player2", "up", right_up);
            settings.set_value("Player2", "down", right_down);
        });
        add_node(apply_button);
    }
}
