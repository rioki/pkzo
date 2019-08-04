// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "CubesEngine.h"

#include "FlyPawn.h"

namespace cubes
{
    CubesEngine::CubesEngine()
    : Engine{"Cubes"}
    {
        on(pkzo::Engine::CHANGE_SCENE, [this] () {
            auto scene = get_scene();
            if (scene)
            {
                auto pawn = std::make_shared<FlyPawn>(*this);
                scene->add_node(pawn);
                set_camera(pawn->get_camera());
            }
        });

        set_scene(create_scene());
    }

    std::shared_ptr<pkzo::Scene> CubesEngine::create_scene()
    {
        auto scene = std::make_shared<pkzo::Scene>();

        auto teapot_mesh = std::make_shared<pkzo::Mesh>("../data/meshes/Teapot.ply");
        auto white_material = std::make_shared<pkzo::Material>("../data/materials/geometry/SolidWhitePhong.pxm");
        auto teapot = std::make_shared<pkzo::MeshGeometry>(teapot_mesh, white_material);
        teapot->move(glm::vec3{0.0f, 0.0f, 0.75f});
        scene->add_node(teapot);

        auto ground = std::make_shared<pkzo::BoxGeometry>(glm::vec3{10.0f, 10.0f, 1.0f}, white_material);
        ground->move(glm::vec3{0.0f, 0.0f, -0.5f});
        scene->add_node(ground);

        auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3(0.1f));
        scene->add_node(light0);

        auto light1 = std::make_shared<pkzo::DirectionalLight>(glm::vec3(0.25f, 0.25f, 0.5f));
        light1->rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
        scene->add_node(light1);

        auto light2 = std::make_shared<pkzo::PointLight>(glm::vec3(0.5f, 0.25f, 0.25f));
        light2->move(glm::vec3{0.0f, 0.0f, 2.0f});
        scene->add_node(light2);

        auto light3 = std::make_shared<pkzo::SpotLight>(glm::vec3(0.5f, 1.0f, 0.5f), glm::radians(45.0f));
        light3->move(glm::vec3{2.0f, 2.0f, 2.0f});
        light3->rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
        scene->add_node(light3);

        return scene;
    }
}
