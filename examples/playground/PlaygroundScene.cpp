
#include "PlaygroundScene.h"

#include <pkzo/Library.h>

#include "PlaygroundEngine.h"

using pkzo::Color;
using pkzo::Vector3;
using pkzo::Quaternion;

namespace pg
{
    PlaygroundScene::PlaygroundScene(PlaygroundEngine& engine)
    {
        pkzo::Library& lib = engine.get_library();

        sky.set_cubemap(lib.load_cubemap("../assets/textures/CloudyAfternoon.jcm"));
        add_node(sky);

        ambient_light.set_color(Color(0.1f, 0.1f, 0.1f));
        add_node(ambient_light);

        sun_light.set_color(Color(0.7f, 0.7f, 0.7f));
        sun_light.set_orientation(pkzo::Quaternion::axis_angle(90.0f, pkzo::Vector3(0, 0, 1)) * 
                                  pkzo::Quaternion::axis_angle(20, pkzo::Vector3(1, 0, 0)));
        add_node(sun_light);

        auto white = lib.load_material("../assets/materials/WhiteBricks.jmn");
        box.set_material(white);
        add_node(box);

    }


    PlaygroundScene::~PlaygroundScene()
    {
    }
}