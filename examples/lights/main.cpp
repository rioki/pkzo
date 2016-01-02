
#include <pkzo.h>
#include <pkzosg.h>

std::shared_ptr<pkzo::Mesh> load_mesh(const std::string& file)
{
    std::shared_ptr<pkzo::Mesh> mesh(new pkzo::Mesh);
    mesh->load(file);
    return mesh;
}

std::shared_ptr<pkzo::Material> load_material(const std::string& file)
{
    std::shared_ptr<pkzo::Material> material(new pkzo::Material);
    material->set_color(pkzo::Color(0xFFF0F0FF));
    return material;
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
    teapot.set_mesh(load_mesh("../assets/meshes/Teapot.ply"));
    teapot.set_material(load_material("../assets/meshes/White.pmd"));
    scene.add_node(teapot);

    pkzo::DirectionalLight light0;
    light0.set_color(pkzo::Color(0xF0F0F0FF));
    scene.add_node(light0);

    pkzo::Camera camera;
    camera.set_position(pkzo::Vector3(0.0, 0.0, 10.0));
    scene.add_node(camera);

    window.on_draw([&] () {
        scene.render(renderer);    
    }); 

    while (running)
    {
        pkzo::route_events();
        window.draw();
    }

    return 0;
}
