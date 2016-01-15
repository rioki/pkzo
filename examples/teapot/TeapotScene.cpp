
#include "TeapotScene.h"

namespace teapot
{
    TeapotScene::TeapotScene(pkzo::Library& library)
    {
        teapot.set_mesh(library.load_mesh("../assets/meshes/Teapot.ply"));
        teapot.set_material(library.load_material("../assets/materials/White.jmn"));
        add_node(teapot);

        light0.set_color(pkzo::Color(0.1f, 0.1f, 0.1f));
        add_node(light0);

        light1.set_color(pkzo::Color(0xFFFFFFFF));
        add_node(light1);
        
        add_node(camera);
    }

    TeapotScene::~TeapotScene()
    {
    }
}
