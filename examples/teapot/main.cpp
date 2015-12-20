
#include <pkzo.h>

int main(int argc, char* argv[])
{
    bool running = true;
    
    pkzo::Window window(800, 600, false);
    
    pkzo::on_quit([&] () {
        running = false;    
    });

    while (running)        
    {
        pkzo::route_events();
        window.draw();
    }
}
