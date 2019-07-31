// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "MaterialsEngine.h"

#include "TestScene.h"
#include "OrbitSpectator.h"

namespace mats
{
    MaterialsEngine::MaterialsEngine()
    : Engine{"Materials"}
    {
        on(pkzo::Engine::CHANGE_SCENE, [this] () {
            auto scene = get_scene();
            if (scene)
            {
                auto spectator = std::make_shared<OrbitSpectator>(*this, glm::vec3(0.0f));
                scene->add_node(spectator);
                set_camera(spectator);
            }
        });

        auto scene = std::make_shared<TestScene>();
        set_scene(scene);
    }
}
