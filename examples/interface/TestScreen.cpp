// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "TestScreen.h"

#include <sstream>
#include <pkzo/pkzo.h>

namespace ui
{
   rgm::vec4 color(unsigned long hex)
    {
        unsigned long r = (0xFF000000 & hex) >> 24;
        unsigned long g = (0x00FF0000 & hex) >> 16;
        unsigned long b = (0x0000FF00 & hex) >> 8;
        unsigned long a = (0x000000FF & hex);  

       rgm::vec4 values;

        values[0] = static_cast<float>(r) / 255.0f;
        values[1] = static_cast<float>(g) / 255.0f;
        values[2] = static_cast<float>(b) / 255.0f;
        values[3] = static_cast<float>(a) / 255.0f;

        return values;
    }

    TestScreen::TestScreen(rgm::ivec2 size)
    : Screen(size)
    {
        auto title_font = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 32);
        auto text_font  = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 18);

        auto button_background   = std::make_shared<pkzo::Texture>("../assets/textures/Button.png");
        auto checkbox_background = std::make_shared<pkzo::Texture>("../assets/textures/CheckBox_Background.png");
        auto checkbox_mark       = std::make_shared<pkzo::Texture>("../assets/textures/CheckBox_Mark.png");
        auto slider_background   = std::make_shared<pkzo::Texture>("../assets/textures/Slider_Background.png");
        auto slider_nob          = std::make_shared<pkzo::Texture>("../assets/textures/Slider_Nob.png");

        set_background_color(color(0x131619FF));

        auto title = std::make_shared<pkzo::Text>();
        title->set_text("Interface Example");    
        title->set_font(title_font);
        title->set_position(rgm::ivec2(50, 50));
        title->set_color(color(0x7C8A99FF));
        add_node(title);

        auto panel = std::make_shared<pkzo::Rectangle>();
        panel->set_color(color(0x292E33FF));
        panel->set_position(rgm::ivec2(50, 150));
        panel->set_size(rgm::ivec2(1180, 568));
        add_node(panel);

        auto button_out = std::make_shared<pkzo::Text>();
        button_out->set_text("<-- Press the Button");
        button_out->set_font(text_font);
        button_out->set_color(color(0x7C8A99FF));
        button_out->set_position(rgm::ivec2(250, 175));
        add_node(button_out);

        auto button = std::make_shared<pkzo::Button>();
        button->set_label("Press Me");
        button->set_label_font(text_font);
        button->set_label_color(color(0x7C8A99FF));
        button->set_background_texture(button_background);
        button->set_background_color(color(0x3E454CFF));
        button->set_position(rgm::ivec2(60, 160));
        button->set_size(rgm::ivec2(170, 50));
        button->on_click([=] () {
            button_out->set_text("#YOLO");
        });
        add_node(button);
    }

    TestScreen::~TestScreen()
    {
    }
}