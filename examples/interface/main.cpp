
#include <pkzo.h>
#include <pkzoui.h>

int main(int argc, char* argv[])
{
    bool running = true;

    pkzo::on_quit([&] () {
        running = false;
    });

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Interface Test");

    while (running)
    {
        pkzo::route_events();

        window.draw();
    }
}
