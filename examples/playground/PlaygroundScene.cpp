
#include "PlaygroundScene.h"

#include <pkzo/Library.h>

#include "PlaygroundEngine.h"

namespace pg
{
    PlaygroundScene::PlaygroundScene(PlaygroundEngine& engine)
    {
        pkzo::Library& lib = engine.get_library();

        sky.set_cubemap(lib.load_cubemap("../assets/textures/CloudyAfternoon.jcm"));
        add_node(sky);
    }


    PlaygroundScene::~PlaygroundScene()
    {
    }
}