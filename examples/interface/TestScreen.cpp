
#include "TestScreen.h"

#include <sstream>
#include <pkzo/Library.h>

using pkzo::Vector2;
using pkzo::Color;

namespace ui
{
    TestScreen::TestScreen(pkzo::Engine& engine)
    : Screen(pkzo::Vector2(1280, 768))
    {
        pkzo::Library& lib = engine.get_library();

        auto title_font = lib.load_font("../assets/fonts/DejaVuSans.ttf", 32);
        auto text_font  = lib.load_font("../assets/fonts/DejaVuSans.ttf", 18);

        auto button_background   = lib.load_texture("../assets/textures/Button.png");
        auto checkbox_background = lib.load_texture("../assets/textures/CheckBox_Background.png");
        auto checkbox_mark       = lib.load_texture("../assets/textures/CheckBox_Mark.png");
        auto slider_background   = lib.load_texture("../assets/textures/Slider_Background.png");
        auto slider_nob          = lib.load_texture("../assets/textures/Slider_Nob.png");

        set_background_color(Color(0x131619FF));

        title.set_text("Interface Example");    
        title.set_font(title_font);
        title.set_position(Vector2(50, 50));
        title.set_color(Color(0x7C8A99FF));
        add_widget(title);

        
        panel.set_color(Color(0x292E33FF));
        panel.set_position(Vector2(50, 150));
        panel.set_size(Vector2(1180, 568));
        add_widget(panel);


        button.set_caption("Press Me");
        button.set_font(text_font);
        button.set_color(Color(0x7C8A99FF));
        button.set_background(button_background);
        button.set_background_color(Color(0x3E454CFF));
        button.set_position(Vector2(60, 160));
        button.set_size(Vector2(170, 50));
        button.on_click([&] () {
            button_out.set_text("#YOLO");
        });
        add_widget(button);

        button_out.set_text("<-- Press the Button");
        button_out.set_font(text_font);
        button_out.set_color(Color(0x7C8A99FF));
        button_out.set_position(Vector2(250, 175));
        add_widget(button_out);


        checkbox.set_caption("Checkbox");
        checkbox.set_font(text_font);
        checkbox.set_color(Color(0x7C8A99FF));
        checkbox.set_background(checkbox_background);
        checkbox.set_background_color(Color(0x3E454CFF));
        checkbox.set_mark(checkbox_mark);
        checkbox.set_mark_color(Color(0x7C8A99FF));
        checkbox.set_position(Vector2(640, 170));
        checkbox.on_toggle([&] () {
            if (checkbox.is_checked())
            {
                checkbox_out.set_text("#YOLO");
            }
            else
            {
                    checkbox_out.set_text("#SWAG");
            }
        });
        add_widget(checkbox);

        checkbox_out.set_text("<-- Check Box");
        checkbox_out.set_font(text_font);
        checkbox_out.set_color(Color(0x7C8A99FF));
        checkbox_out.set_position(Vector2(800, 175));
        add_widget(checkbox_out);

        
        slider.set_background(slider_background);
        slider.set_background_color(Color(0x3E454CFF));
        slider.set_nob(slider_nob);
        slider.set_nob_color(Color(0x7C8A99FF));
        slider.set_increments(11);
        slider.set_value(3);
        slider.set_position(Vector2(60, 270));
        slider.on_change([&] () {
            std::stringstream buff;
            buff << slider.get_value() * 10 << "%";
            slider_out.set_text(buff.str());
        });
        add_widget(slider);

        slider_out.set_text("30 %");
        slider_out.set_font(text_font);
        slider_out.set_color(Color(0x7C8A99FF));
        slider_out.set_position(Vector2(350, 275));
        add_widget(slider_out);
    }

    TestScreen::~TestScreen()
    {
    }
}