
#include <sstream>
#include <pkzo.h>
#include <pkzoui.h>

std::shared_ptr<pkzo::Texture> load_texture(const std::string& file)
{
    std::shared_ptr<pkzo::Texture> texture(new pkzo::Texture);
    texture->load(file);
    return texture;
}

std::shared_ptr<pkzo::Font> load_font(const std::string& file, unsigned int size)
{
    std::shared_ptr<pkzo::Font> font(new pkzo::Font);
    font->load(file, size);
    return font;
}

int main(int argc, char* argv[])
{
    bool running = true;

    pkzo::on_quit([&] () {
        running = false;
    });

    auto title_font = load_font("../assets/fonts/DejaVuSans.ttf", 32);
    auto text_font  = load_font("../assets/fonts/DejaVuSans.ttf", 18);

    auto button_background   = load_texture("../assets/textures/Button.png");
    auto checkbox_background = load_texture("../assets/textures/CheckBox_Background.png");
    auto checkbox_mark       = load_texture("../assets/textures/CheckBox_Mark.png");
    auto slider_background   = load_texture("../assets/textures/Slider_Background.png");
    auto slider_nob          = load_texture("../assets/textures/Slider_Nob.png");

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Interface Example");

    pkzo::Mouse mouse;

    pkzo::ScreenRenderer screen_renderer;
    
    pkzo::Screen screen(1280, 768);
    screen.set_background_color(pkzo::Color(0x131619FF));

    pkzo::Text title;
    title.set_text("Interface Example");    
    title.set_font(title_font);
    title.set_position(50, 50);
    title.set_color(pkzo::Color(0x7C8A99FF));
    screen.add_widget(title);
    
    // TODO make this a real panel
    pkzo::Rectangle panel;
    panel.set_color(pkzo::Color(0x292E33FF));
    panel.set_position(50, 150);
    panel.set_size(1180, 568);
    screen.add_widget(panel);

    pkzo::Text button_out;
    button_out.set_text("<-- Press the Button");
    button_out.set_font(text_font);
    button_out.set_color(pkzo::Color(0x7C8A99FF));
    button_out.set_position(250, 175);
    screen.add_widget(button_out);
    
    pkzo::Button button;
    button.set_caption("Press Me");
    button.set_font(text_font);
    button.set_color(pkzo::Color(0x7C8A99FF));
    button.set_background(button_background);
    button.set_background_color(pkzo::Color(0x3E454CFF));
    button.set_position(60, 160);
    button.set_size(170, 50);
    button.on_click([&] () {
        button_out.set_text("#YOLO");
    });
    screen.add_widget(button);

    pkzo::Text checkbox_out;
    checkbox_out.set_text("<-- Check Box");
    checkbox_out.set_font(text_font);
    checkbox_out.set_color(pkzo::Color(0x7C8A99FF));
    checkbox_out.set_position(800, 175);
    screen.add_widget(checkbox_out);

    pkzo::CheckBox checkbox;
    checkbox.set_caption("Checkbox");
    checkbox.set_font(text_font);
    checkbox.set_color(pkzo::Color(0x7C8A99FF));
    checkbox.set_background(checkbox_background);
    checkbox.set_background_color(pkzo::Color(0x3E454CFF));
    checkbox.set_mark(checkbox_mark);
    checkbox.set_mark_color(pkzo::Color(0x7C8A99FF));
    checkbox.set_position(640, 170);
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
    screen.add_widget(checkbox);

    pkzo::Text slider_out;
    slider_out.set_text("30 %");
    slider_out.set_font(text_font);
    slider_out.set_color(pkzo::Color(0x7C8A99FF));
    slider_out.set_position(350, 275);
    screen.add_widget(slider_out);

    pkzo::Slider slider;
    slider.set_background(slider_background);
    slider.set_background_color(pkzo::Color(0x3E454CFF));
    slider.set_nob(slider_nob);
    slider.set_nob_color(pkzo::Color(0x7C8A99FF));
    slider.set_increments(11);
    slider.set_value(3);
    slider.set_position(60, 270);
    slider.on_change([&] () {
        std::stringstream buff;
        buff << slider.get_value() * 10 << "%";
        slider_out.set_text(buff.str());
    });
    screen.add_widget(slider);


    window.on_draw([&] () {
        screen.draw(screen_renderer);
    });

    mouse.on_move([&] (unsigned int x, unsigned int y, int dx, int dy) {
        screen.handle_mouse_move(x, y, dx, dy);
    });

    mouse.on_button_press([&] (unsigned int btn, unsigned int x, unsigned int y) {
        screen.handle_mouse_down(btn, x, y);
    });

    mouse.on_button_release([&] (unsigned int btn, unsigned int x, unsigned int y) {
        screen.handle_mouse_up(btn, x, y);
    });

    while (running)
    {
        pkzo::route_events();

        window.draw();
    }
}
