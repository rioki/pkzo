// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "SettingsMenu.h"

#include <pkzo/color.h>

#include "env.h"
#include "Settings.h"

namespace island
{
    using namespace pkzo2d;

    SettingsMenu::SettingsMenu(Init init)
    : Screen({
        .size = init.size
      })
    {
        auto size      = get_size();
        auto half_size = size / 2.0f;

        auto base = get_asset_folder();
        auto ui_style = Settings(base / "ui/Menu.yml");


        add<Text>({
            .transform = position(0.0f, half_size.y * 0.5f),
            .text      = u8"Settings",
            .color     = ui_style.get<pkzo::color4>("logo", "text_color"),
            .font      = pkzo::Font::load(base / ui_style.get<std::string>("logo", "font")),
            .font_size = ui_style.get<unsigned int>("logo", "font_size")
        });

        add<Text>({
            .transform = position(glm::vec2(0.0f, half_size.y * 0.5f) + glm::vec2(0.0f, -100.0f)),
            .text      = u8"For now, just edit %LOCALAPPDATA%/pkzo/island/settings.yml",
            .color     = ui_style.get<pkzo::color4>("text", "text_color"),
            .font      = pkzo::Font::load(base / ui_style.get<std::string>("text", "font")),
            .font_size = ui_style.get<unsigned int>("text", "font_size"),
        });

        auto* settings_text = add<Text>({
            .transform = position(0.0f, -50.0f),
            .text      = u8"Back",
            .color     = ui_style.get<pkzo::color4>("button", "text_color"),
            .font      = pkzo::Font::load(base / ui_style.get<std::string>("button", "font")),
            .font_size = ui_style.get<unsigned int>("button", "font_size"),
        });

        add<HitArea>({
            .transform = settings_text->get_transform(),
            .size      = settings_text->get_size(),
            .action    = init.back_action
        });


       add<Text>({
            .transform = position(0.0f, -half_size.y + 30.0f),
            .text      = u8"Yes, this is a placeholder...",
            .color     = ui_style.get<pkzo::color4>("footer", "text_color"),
            .font      = pkzo::Font::load(base / ui_style.get<std::string>("footer", "font")),
            .font_size = ui_style.get<unsigned int>("footer", "font_size"),
        });
    }
}