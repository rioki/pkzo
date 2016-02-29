/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "TestScene.h"

namespace pm
{
    std::shared_ptr<pkzo::Mesh> load_mesh(const std::string& file)
    {
        std::shared_ptr<pkzo::Mesh> mesh(new pkzo::Mesh);
        mesh->load(file);
        return mesh;
    }

    TestScene::TestScene()
    : cam_pos(0, 90, 10)
    {
        meshes.push_back(load_mesh("../assets/meshes/Box.ply"));
        meshes.push_back(load_mesh("../assets/meshes/Sphere.ply"));
        meshes.push_back(load_mesh("../assets/meshes/Teapot.ply"));
        
        camera.set_position(rgm::vec3(0, 0, 5));
        rotate_camera(rgm::ivec2(0, 0));
        add_entity(camera);

        
        add_entity(light0);
        
        material.reset(new pkzo::Material);
        material->set_albedo(rgm::vec3(1, 0.765557, 0.336057));

        subject.set_mesh(meshes[0]);
        subject.set_material(material);
        add_entity(subject);


        std::shared_ptr<pkzo::CubeMap> cubemap(new pkzo::CubeMap);
        cubemap->load("../assets/textures/Morning_XPos.jpg", "../assets/textures/Morning_XNeg.jpg",
                      "../assets/textures/Morning_YPos.jpg", "../assets/textures/Morning_YNeg.jpg",
                      "../assets/textures/Morning_ZPos.jpg", "../assets/textures/Morning_ZNeg.jpg");
        sky.set_cubemap(cubemap);
        add_entity(sky);
    }

    TestScene::~TestScene() {}

    pkzo::Camera& TestScene::get_camera()
    {
        return camera;
    }

    void TestScene::change_mesh(MeshId id)
    {
        assert(id < meshes.size());
        subject.set_mesh(meshes[id]);
    }

    void TestScene::rotate_camera(rgm::ivec2 mov)
    {
        cam_pos[0] += (float)mov[0];
        cam_pos[1] += (float)mov[1];

        rgm::quat co = rgm::axis_angle(rgm::vec3(0, 0, 1), cam_pos[0]) *
                        rgm::axis_angle(rgm::vec3(1, 0, 0), cam_pos[1]) 
                       ;
        
        rgm::vec3 cp = rgm::transform(co, rgm::vec3(0, 0, cam_pos[2]));

        camera.set_orientation(co);
        //camera.set_position(cp);         
    }
}
