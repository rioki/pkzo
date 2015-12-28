
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

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Interface Example");

    pkzoui::ScreenRenderer screen_renderer;
    
    pkzoui::Screen screen(1280, 768);
    screen.set_background_color(pkzoui::Color(0x131619FF));

    pkzoui::Text title;
    title.set_text("Interface Example");    
    title.set_font(title_font);
    title.set_position(50, 50);
    title.set_color(pkzoui::Color(0x7C8A99FF));
    screen.add_widget(title);
    
    pkzoui::Rectangle left_pannel;
    left_pannel.set_color(pkzoui::Color(0x292E33FF));
    left_pannel.set_position(50, 150);
    left_pannel.set_size(1180, 568);
    screen.add_widget(left_pannel);

    window.on_draw([&] () {
        screen.draw(screen_renderer);
    });

    while (running)
    {
        pkzo::route_events();

        window.draw();
    }
}
