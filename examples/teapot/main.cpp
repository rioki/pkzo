

#include <pkzo.h>

#include <gl/glew.h>
#include "glm.h"

int main(int argc, char* argv[])
{
    bool  running = true;
    float a       = 0.0f;
    float projection[16];
    float modelview[16];

    pkzo::Window window(800, 600);
    window.set_title("pkzo - Teapot Demo");
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Mesh mesh;
    //mesh.create_plane(10, 10);
    mesh.load("Teapot.ply");

    pkzo::Shader shader;
    shader.load("PhongVertex.glsl", "PhongFragment.glsl");

    pkzo::Texture steel_plate;
    steel_plate.load("SteelPlate_Diffuse.png");
  
    glmPerspective(projection, 45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    
    window.on_draw([&] () {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        a += 1.0;
        glmLoadIdentity(modelview);
        glmLookAt(modelview, 5, 5, 5, 0, 0, 0, 0, 0, 1);
        glmRotate(modelview, a, 1, 0.5, 0);

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
