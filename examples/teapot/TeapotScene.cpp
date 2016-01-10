
#include "TeapotScene.h"

namespace teapot
{
    TeapotScene::TeapotScene(pkzo::Library& library)
    {
        teapot.set_mesh(library.load_mesh("../assets/meshes/Teapot.ply"));
        teapot.set_material(library.load_material("../assets/materials/White.jmn"));
        add_node(teapot);

        light0.set_color(pkzo::Color(0xFFFFFFFF));
        add_node(light0);

        camera.set_position(pkzo::Vector3(0, 0, 10));
        add_node(camera);
    }

    TeapotScene::~TeapotScene()
    {
    }
}
