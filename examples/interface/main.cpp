
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

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Interface Test");

    pkzoui::ScreenRenderer screen_renderer;
    
    pkzoui::Screen screen(1280, 768);
    screen.set_background_color(0.75f, 0.2f, 0.5f, 1.0f);
    screen.set_background_texture(load_texture("../teapot/SteelPlate_Diffuse.png"));

    pkzoui::Image image;
    image.set_texture(load_texture("../teapot/SteelPlate_Diffuse.png"));
    image.set_position(150, 150);
    image.set_size(150, 150);
    screen.add_widget(image);

    pkzoui::Text text;
    text.set_font(load_font("../assets/fonts/DejaVuSans.ttf", 24));
    text.set_text("Hello World!");
    text.set_position(250, 250);
    screen.add_widget(text);

    window.on_draw([&] () {
        screen.draw(screen_renderer);
    });

    while (running)
    {
        pkzo::route_events();

        window.draw();
    }
}
