

#include <pkzo.h>

#include "glm.h"

int main(int argc, char* argv[])
{
    bool running = true;
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Mesh mesh;
    mesh.set_vertex_count(3);    

    mesh.set_vertex(0, 0.0, 0.0, 0.0);
    mesh.set_color(0, 1.0, 0.0, 0.0, 1.0);

    mesh.set_vertex(1, 0.0, 1.0, 0.0);
    mesh.set_color(1, 0.0, 1.0, 0.0, 1.0);

    mesh.set_vertex(2, 1.0, 0.0, 0.0);
    mesh.set_color(2, 0.0, 0.0, 1.0, 1.0);

    mesh.set_face_count(1);
    mesh.set_face(0, 0, 1, 2);


    pkzo::Shader shader;
    shader.load("PhongVertex.glsl", "PhongFragment.glsl");
  
    float projection[16];
    float modelview[16];

    glmPerspective(projection, 45.0f, 800.0f/600.0f, 0.1f, 100.0f);

    glmLoadIdentity(modelview);
    glmTranslate(modelview, 0, 0, -2);

    pkzo::Window window(800, 600);
    window.set_title("pkzo - Teapot Demo");
    window.on_draw([&] () {
        shader.bind();
        shader.set_uniform_matrix("uProjection", projection, 16);
        shader.set_uniform_matrix("uModelView",  modelview,  16);

        mesh.draw(shader);
    });    
    

    while (running)        
    {
        pkzo::route_events();
        window.draw();
    }
}
