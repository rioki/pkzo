
#include "TestScreen.h"

#include <sstream>
#include <pkzo/pkzo.h>

namespace ui
{
    std::shared_ptr<pkzo::Font> load_font(const std::string& file, unsigned int size)
    {
        std::shared_ptr<pkzo::Font> font(new pkzo::Font);
        font->load(file, size);
        return font;
    }

    std::shared_ptr<pkzo::Texture> load_texture(const std::string& file)
    {
        std::shared_ptr<pkzo::Texture> texture(new pkzo::Texture);
        texture->load(file);
        return texture;
    }

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
        auto title_font = load_font("../assets/fonts/DejaVuSans.ttf", 32);
        auto text_font  = load_font("../assets/fonts/DejaVuSans.ttf", 18);

        auto button_background   = load_texture("../assets/textures/Button.png");
        auto checkbox_background = load_texture("../assets/textures/CheckBox_Background.png");
        auto checkbox_mark       = load_texture("../assets/textures/CheckBox_Mark.png");
        auto slider_background   = load_texture("../assets/textures/Slider_Background.png");
        auto slider_nob          = load_texture("../assets/textures/Slider_Nob.png");

        set_background_color(color(0x131619FF));

        title.set_text("Interface Example");    
        title.set_font(title_font);
        title.set_position(rgm::ivec2(50, 50));
        title.set_color(color(0x7C8A99FF));
        add_widget(title);

        
        panel.set_color(color(0x292E33FF));
        panel.set_position(rgm::ivec2(50, 150));
        panel.set_size(rgm::ivec2(1180, 568));
        add_widget(panel);


        button.set_label("Press Me");
        button.set_label_font(text_font);
        button.set_label_color(color(0x7C8A99FF));
        button.set_background_texture(button_background);
        button.set_background_color(color(0x3E454CFF));
        button.set_position(rgm::ivec2(60, 160));
        button.set_size(rgm::ivec2(170, 50));
        button.on_click([&] () {
            button_out.set_text("#YOLO");
        });
        add_widget(button);

        button_out.set_text("<-- Press the Button");
        button_out.set_font(text_font);
        button_out.set_color(color(0x7C8A99FF));
        button_out.set_position(rgm::ivec2(250, 175));
        add_widget(button_out);


        /*checkbox.set_caption("Checkbox");
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
        add_widget(slider_out);*/
    }

    TestScreen::~TestScreen()
    {
    }
}