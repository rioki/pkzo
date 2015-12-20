
#include <pkzo.h>

int main(int argc, char* argv[])
{
    bool running = true;
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Window window(800, 600);
    window.on_draw([&] () {
        // openGL stuff
    });    
    

    while (running)        
    {
        pkzo::route_events();
        window.draw();
    }
}
