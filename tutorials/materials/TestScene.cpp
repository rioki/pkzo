// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "TestScene.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mats
{
    TestScene::TestScene()
    {
        auto teapot_mesh = std::make_shared<pkzo::Mesh>("../data/meshes/Teapot.ply");
        auto white_material = std::make_shared<pkzo::Material>("../data/materials/geometry/SolidWhitePhong.pxm");
        auto teapot = std::make_shared<pkzo::MeshGeometry>(teapot_mesh, white_material);
        teapot->move(glm::vec3{0.0f, 0.0f, 0.75f});
        add_node(teapot);

        auto ground = std::make_shared<pkzo::BoxGeometry>(glm::vec3{10.0f, 10.0f, 1.0f}, white_material);
        ground->move(glm::vec3{0.0f, 0.0f, -0.5f});
        add_node(ground);

        auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3(0.1f));
        add_node(light0);

        auto light1 = std::make_shared<pkzo::DirectionalLight>(glm::vec3(0.25f, 0.25f, 0.5f));
        light1->set_transform(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f)));
        add_node(light1);
    }
}
