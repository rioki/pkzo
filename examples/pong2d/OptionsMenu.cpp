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
    using pkzo::position;

    OptionsMenu::OptionsMenu(Game& game)
    : Screen(glm::vec2(800, 600))
    {
        auto title_font                 = std::make_shared<pkzo::Font>("../assets/fonts/KarmicArcade.ttf", 30);
        auto text_font                  = std::make_shared<pkzo::Font>("../assets/fonts/Hardpixel.ttf", 20);

        auto text_material              = pkzo::make_emissive_material(glm::vec3(0.9f));
        
        auto button_background_texture  = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Button_Background.png");
        auto button_size                = button_background_texture->get_size();
        auto button_background          = pkzo::make_emissive_material(button_background_texture);
        auto button_text                = pkzo::make_emissive_material(glm::vec3(0.2f));

        auto checkbox_checked_texture   = std::make_shared<pkzo::Texture>("../assets/ui/pixels/CheckBox_Checked.png");
        auto checkbox_unchecked_texture = std::make_shared<pkzo::Texture>("../assets/ui/pixels/CheckBox_Unchecked.png");
        assert(checkbox_checked_texture->get_size() == checkbox_unchecked_texture->get_size());
        auto checkbox_size              = checkbox_checked_texture->get_size();
        auto checkbox_checked           = pkzo::make_emissive_material(checkbox_checked_texture);
        auto checkbox_unchecked         = pkzo::make_emissive_material(checkbox_unchecked_texture);

        auto slider_background_texture  = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Slider_Horizontal_200.png");
        auto slider_size                = slider_background_texture->get_size();
        auto slider_background          = pkzo::make_emissive_material(slider_background_texture);
        auto slider_handle_texture      = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Slider_Handle.png");
        auto slider_handle_size         = slider_handle_texture->get_size();
        auto slider_handle              = pkzo::make_emissive_material(slider_handle_texture);

        auto dropdown_background_texture = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Dropdown_200_Background.png");
        auto dropdown_size               = dropdown_background_texture->get_size();
        auto dropdown_background         = pkzo::make_emissive_material(dropdown_background_texture);
        auto dropdown_button_texture     = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Dropdown_Button.png");
        auto dropdown_button_size        = dropdown_button_texture->get_size();
        auto dropdown_button             = pkzo::make_emissive_material(dropdown_button_texture);
        auto dropdown_label              = pkzo::make_emissive_material(glm::vec3(0.1f));

        auto menu_top_texture             = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Top.png");
        auto menu_top_size                = menu_top_texture->get_size();
        auto menu_top                     = pkzo::make_emissive_material(menu_top_texture);
        auto menu_body_texture            = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Body.png");
        auto menu_body_size               = menu_body_texture->get_size();
        auto menu_body                    = pkzo::make_emissive_material(menu_body_texture);
        auto menu_bottom_texture          = std::make_shared<pkzo::Texture>("../assets/ui/pixels/Menu_200_Bottom.png");
        auto menu_bottom_size             = menu_bottom_texture->get_size();
        auto menu_bottom                  = pkzo::make_emissive_material(menu_bottom_texture);

        auto& settings = game.get_settings();

        auto title = std::make_shared<pkzo::Text>(position(0.0f, 250.0f), "Options", title_font, text_material);
        add_node(title);

        auto resolution_label = std::make_shared<pkzo::Text>(position({ -390.0f + text_font->estimate("Resolution").x / 2.0f, 150.0f }), "Resolution", text_font, text_material);
        add_node(resolution_label);
        auto fullscren_label = std::make_shared<pkzo::Text>(position({ -390.0f + text_font->estimate("Fullscreen").x / 2.0f, 100.0f }), "Fullscreen", text_font, text_material);
        add_node(fullscren_label);

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
        auto resolution_value = std::make_shared<pkzo::DropDownMenu>(position({ -10.0f - dropdown_size.x / 2.0f, 150.0f }), 
                                                                     dropdown_size, dropdown_background, 
                                                                     dropdown_button_size, dropdown_button, 
                                                                     menu_top_size, menu_body_size, menu_bottom_size,
                                                                     menu_top, menu_body, menu_bottom,
                                                                     text_font, dropdown_label, resolution_text, index);
        add_node(resolution_value);


        auto fullscreen = settings.get_value("Video", "fullscreen", false);
        auto fullscreen_value = std::make_shared<pkzo::CheckBox>(position({ -10.0f - slider_size.x / 2.0f, 100.0f }), checkbox_size, checkbox_checked, checkbox_unchecked, fullscreen);
        add_node(fullscreen_value);

        auto music_volume_label = std::make_shared<pkzo::Text>(position({ -390.0f + text_font->estimate("Music Volume").x / 2.0f, -50.0f }), "Music Volume", text_font, text_material);
        add_node(music_volume_label);
        auto sfx_volume_label = std::make_shared<pkzo::Text>(position({ -390.0f + text_font->estimate("SFX Volume").x / 2.0f, -100.0f }), "SFX Volume", text_font, text_material);
        add_node(sfx_volume_label);

        auto music_volume = settings.get_value("Sound", "music_volume", 0.7f);
        auto music_volume_value = std::make_shared<pkzo::Slider>(position({ -10.0f - slider_size.x / 2.0f, -50.0f }), pkzo::SliderOrientation::HORIZONTAL, slider_size, slider_background, slider_handle_size, slider_handle, music_volume);
        add_node(music_volume_value);

        auto sfx_volume = settings.get_value("Sound", "sfx_volume", 0.7f);
        auto sfx_volume_value = std::make_shared<pkzo::Slider>(position({ -10.0f - slider_size.x / 2.0f, -100.0f }), pkzo::SliderOrientation::HORIZONTAL, slider_size, slider_background, slider_handle_size, slider_handle, sfx_volume);
        add_node(sfx_volume_value);

        auto p1_up_label = std::make_shared<pkzo::Text>(position({ 10.0f + text_font->estimate("Player 1 Up").x / 2.0f, 150.0f }), "Player 1 Up", text_font, text_material);
        add_node(p1_up_label);
        auto p1_down_label = std::make_shared<pkzo::Text>(position({ 10.0f + text_font->estimate("Player 1 Down").x / 2.0f, 100.0f }), "Player 1 Down", text_font, text_material);
        add_node(p1_down_label);
        auto p2_up_label = std::make_shared<pkzo::Text>(position({ 10.0f + text_font->estimate("Player 2 Up").x / 2.0f, 50.0f }), "Player 2 Up", text_font, text_material);
        add_node(p2_up_label);
        auto p2_down_label = std::make_shared<pkzo::Text>(position({ 10.0f + text_font->estimate("Player 2 Down").x / 2.0f, 0.0f }), "Player 2 Down", text_font, text_material);
        add_node(p2_down_label);

        auto p1_up_value = std::make_shared<KeyInput>(position({ 250.0f, 150.0f }), text_font, text_material, settings.get_value("Player1", "up", pkzo::Key::Q));
        p1_up_value->on_click([&game, p1_up_value] () {
            game.capture_key([p1_up_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p1_up_value->set_key(key);
                }
            });
        });
        add_node(p1_up_value);

        auto p1_down_value = std::make_shared<KeyInput>(position({ 250.0f, 100.0f }), text_font, text_material, settings.get_value("Player1", "down", pkzo::Key::A));
        p1_down_value->on_click([&game, p1_down_value] () {
            game.capture_key([p1_down_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p1_down_value->set_key(key);
                }
            });
        });
        add_node(p1_down_value);

        auto p2_up_value = std::make_shared<KeyInput>(position({ 250.0f, 50.0f }), text_font, text_material, settings.get_value("Player2", "up", pkzo::Key::P));
        p2_up_value->on_click([&game, p2_up_value] () {
            game.capture_key([p2_up_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p2_up_value->set_key(key);
                }
            });
        });
        add_node(p2_up_value);

        auto p2_down_value = std::make_shared<KeyInput>(position({ 250.0f, 0.0f }), text_font, text_material, settings.get_value("Player2", "down", pkzo::Key::L));
        p2_down_value->on_click([&game, p2_down_value] () {
            game.capture_key([p2_down_value] (auto mod, auto key) {
                if (key != pkzo::Key::ESCAPE)
                {
                    p2_down_value->set_key(key);
                }
            });
        });
        add_node(p2_down_value);

        auto back_button = std::make_shared<pkzo::Button>(position(165, -270.0f), "Back", button_size, button_background, button_text, text_font);
        back_button->on_click([&game] () {
            game.change_state(GameState::MAIN_MENU);
        });
        add_node(back_button);

        auto apply_button = std::make_shared<pkzo::Button>(position(320.0f, -270.0f), "Apply", button_size, button_background, button_text, text_font);
        apply_button->on_click([=, &game] () {
            auto& settings = game.get_settings();

            game.change_state(GameState::MAIN_MENU);

            auto res_idx = resolution_value->get_selected_option();
            assert(res_idx);
            auto res = resolutions[res_idx.value()];
            auto fullscreen = fullscreen_value->get_checked();

            game.get_window().resize(res, fullscreen ? pkzo::WindowMode::FULLSCREEN : pkzo::WindowMode::STATIC);
            settings.set_value("Graphic", "resolution", res);
            settings.set_value("Graphic", "fullscreen", fullscreen);

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
