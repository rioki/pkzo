

#include <pkzo.h>

#include <gl/glew.h>
#include "glm.h"

int main(int argc, char* argv[])
{
    bool  running = true;
    float ax      = 0.0f;
    float ay      = 0.0f;
    float projection[16];
    float modelview[16];

    pkzo::Window window(800, 600);
    window.set_title("pkzo - Teapot Demo");

    pkzo::Keyboard keyboard;
    keyboard.on_key_press([&] (pkzo::Key key) {
        if (key == pkzo::KEY_ESCAPE)
        {
            running = false;
        }
    });

    pkzo::Mouse mouse;
    mouse.on_move([&] (unsigned int x, unsigned int y, int dx, int dy) {
        if (mouse.is_pressed(1))        
        {
            ax += static_cast<float>(dx);
            ay += static_cast<float>(dy);
        }
    });
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Mesh mesh;
    mesh.load("Teapot.ply");

    pkzo::Shader shader;
    shader.load("PhongVertex.glsl", "PhongFragment.glsl");

    pkzo::Texture steel_plate;
    steel_plate.load("SteelPlate_Diffuse.png");
  
    glmPerspective(projection, 45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    
    window.on_draw([&] () {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        glmLoadIdentity(modelview);
        glmLookAt(modelview, 5, 5, 5, 0, 0, 0, 0, 0, 1);
        glmRotate(modelview, ax, 0, 1, 0);
        glmRotate(modelview, ay, 1, 0, 0);        

        shader.bind();
        shader.set_uniform_matrix("uProjection", projection, 16);
        shader.set_uniform_matrix("uModelView",  modelview,  16);

        steel_plate.bind(0);
        shader.set_uniform("uTexture", 0);

        mesh.draw(shader);
    });        

    while (running)        
    {
        pkzo::route_events();
        window.draw();
    }
}
