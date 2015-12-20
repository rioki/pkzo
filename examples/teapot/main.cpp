
#include <pkzo.h>

int main(int argc, char* argv[])
{
    bool running = true;
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Shader shader;
    shader.load("PhongVertex.glsl", "PhongFragment.glsl");

    float projection[16] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1};
    float modelview[16] = {1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1};

    pkzo::Window window(800, 600);
    window.set_title("pkzo - Teapot Demo");
    window.on_draw([&] () {
        shader.bind();
        shader.set_uniform_matrix("uProjection", projection, 16);
        shader.set_uniform_matrix("uModelView", modelview, 16);

    });    
    

    while (running)        
    {
        pkzo::route_events();
        window.draw();
    }
}
