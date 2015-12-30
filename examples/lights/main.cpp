
#include <pkzo.h>
#include <pkzosg.h>

std::shared_ptr<pkzo::Mesh> load_mesh(const std::string& file)
{
    std::shared_ptr<pkzo::Mesh> mesh(new pkzo::Mesh);
    mesh->load(file);
    return mesh;
}

int main(int argc, char* arv[])
{
    bool  running = true;
    
    pkzo::on_quit([&]() {
        running = false;
    });

    pkzo::Window window(1280, 768);
    window.set_title("pkzo - Lights");

    pkzo::SceneRenderer renderer;

    pkzo::Scene scene;

    pkzo::Geometry teapot;


    while (running)
    {
        pkzo::route_events();
        window.draw();
    }

    return 0;
}
