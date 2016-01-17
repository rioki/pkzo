
#include "TeapotScene.h"

namespace teapot
{
    TeapotScene::TeapotScene(pkzo::Library& library)
    {
        
        sky.set_cubemap(library.load_cubemap("../assets/textures/Morning.jcm"));
        add_node(sky);

        light0.set_color(pkzo::Color(0x644320FF));
        add_node(light0);

        light1.set_color(pkzo::Color(0xCFCFC5FF));
        light1.set_orientation(pkzo::Quaternion::axis_angle(-135, pkzo::Vector3(0, 0, 1)) * 
                               pkzo::Quaternion::axis_angle(45, pkzo::Vector3(1, 0, 0)));
        add_node(light1);
        
        teapot.set_mesh(library.load_mesh("../assets/meshes/Teapot.ply"));
        teapot.set_material(library.load_material("../assets/materials/White.jmn"));
        add_node(teapot);

        add_node(camera);
    }

    TeapotScene::~TeapotScene()
    {
    }
}
