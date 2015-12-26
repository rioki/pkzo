
#include <pkzo.h>
#include <pkzoui.h>

std::shared_ptr<pkzo::Texture> load_texture(const std::string& file)
{
    std::shared_ptr<pkzo::Texture> texture(new pkzo::Texture);
    texture->load(file);
    return texture;
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
    screen.set_background_color(0.75, 0.2, 0.5, 1.0);
    screen.set_background_texture(load_texture("../teapot/SteelPlate_Diffuse.png"));

    window.on_draw([&] () {
        screen.draw(screen_renderer);
    });

    while (running)
    {
        pkzo::route_events();

        window.draw();
    }
}
