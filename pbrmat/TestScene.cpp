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
    TestScene::TestScene()
    {
        mesh.reset(new pkzo::Mesh);
        mesh->create_box(rgm::vec3(1));

        material.reset(new pkzo::Material);
        material->set_albedo(rgm::vec3(1, 0, 0));

        camera.set_position(rgm::vec3(0, 0, 10));
        add_entity(camera);

        add_entity(light0);

        subject.set_mesh(mesh);
        subject.set_material(material);
        add_entity(subject);
    }

    TestScene::~TestScene() {}

    pkzo::Camera& TestScene::get_camera()
    {
        return camera;
    }
}
