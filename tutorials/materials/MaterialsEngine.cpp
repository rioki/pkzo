// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "MaterialsEngine.h"

#include "TestScene.h"

namespace mats
{
    MaterialsEngine::MaterialsEngine()
    : Engine{"Materials"}
    {
        auto scene = std::make_shared<TestScene>();
        set_scene(scene);
        set_camera(scene->get_camera());
    }
}
