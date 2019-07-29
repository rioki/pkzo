// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "TestScene.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mats
{
    TestScene::TestScene()
    {
        auto cam_position = glm::mat4(1.0f);
        cam_position = glm::translate(cam_position, glm::vec3(0.0f, 0.0f, 10.f));
        camera = std::make_shared<pkzo::Camera>();
        camera->set_transform(cam_position);
        add_node(camera);

        auto teapot_mesh = std::make_shared<pkzo::Mesh>("../data/meshes/Teapot.ply");
        auto white_material = std::make_shared<pkzo::Material>("../data/materials/geometry/SolidWhitePhong.pxm");
        auto teapot = std::make_shared<pkzo::Geometry>();
        teapot->set_mesh(teapot_mesh);
        teapot->set_material(white_material);
        add_node(teapot);

        auto light0 = std::make_shared<pkzo::AmbientLight>(glm::vec3(0.25f));
        add_node(light0);
    }

    std::shared_ptr<pkzo::Camera> TestScene::get_camera() const
    {
        return camera;
    }
}
