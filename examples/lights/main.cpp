
#include <pkzo.h>
#include <pkzosg.h>

int main(int argc, char* arv[])
{
    bool  running = true;
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Lights");

    pkzo::Scene scene;

    while (running)
    {
        pkzo::route_events();
        window.draw();
    }

    return 0;
}
