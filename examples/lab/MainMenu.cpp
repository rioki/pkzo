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

#include "MainMenu.h"

#include <pkzo/strconv.h>

#include "tinyformat.h"
#include "env.h"
#include "App.h"

namespace lab
{
    using namespace pkzo2d;

    constexpr auto PRIMARY_COLOR    = glm::vec4(1.0f);
    constexpr auto FONT             = "fonts/DejaVuSansMono.ttf";
    constexpr auto TITLE_FONT_SIZE  = 32u;
    constexpr auto BUTTON_FONT_SIZE = 24u;
    constexpr auto TEXT_FONT_SIZE   = 18u;

    MainMenu::MainMenu(App& app, const glm::vec2& size)
    : Screen({
        .size = size
      })
    {
        auto half_size = size / 2.0f;

        auto base = get_asset_folder();
        auto font = pkzo::Font::load(base / FONT);

        add<Text>({
            .transform = position(0.0f, half_size.y * 0.5f),
            .text      = strconv::utf8(tfm::format("pkzo lab %s", VERSION)),
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = TITLE_FONT_SIZE
        });

        add<Text>({
            .transform = position(glm::vec2(0.0f, half_size.y * 0.5f) + glm::vec2(0.0f, -50.0f)),
            .text      = u8"We break things, so you don't have to.",
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = TEXT_FONT_SIZE
        });

        auto* material_test = add<Text>({
            .transform = position(0.0f, 0.0f),
            .text      = u8"Material Test",
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = BUTTON_FONT_SIZE
        });

        add<HitArea>({
            .transform = material_test->get_transform(),
            .size      = material_test->get_size(),
            .action    = [&] () { app.start_material_test(); }
        });

        auto* physics_test = add<Text>({
            .transform = position(0.0f, -50.0f),
            .text      = u8"Pysics Test",
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = BUTTON_FONT_SIZE
        });

        add<HitArea>({
            .transform = physics_test->get_transform(),
            .size      = physics_test->get_size(),
            .action    = [&] () { app.start_physics_test(); }
        });

        auto* exit_text = add<Text>({
            .transform = position(0.0f, -100.0f),
            .text      = u8"Exit",
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = BUTTON_FONT_SIZE
        });

        add<HitArea>({
            .transform = exit_text->get_transform(),
            .size      = exit_text->get_size(),
            .action    = [&] () { app.stop(); }
        });

        add<Text>({
            .transform = position(0.0f, -half_size.y + 30.0f),
            .text      = u8"Copyright 2026 Sean Farrell",
            .color     = PRIMARY_COLOR,
            .font      = font,
            .font_size = TEXT_FONT_SIZE
        });
    }
}