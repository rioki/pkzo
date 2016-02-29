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

#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include <vector>
#include <pkzo/pkzo.h>
#include <pkzo3d/pkzo3d.h>

namespace pm
{
    enum MeshId
    {
        BOX_MESH,
        SPHERE_MESH,
        TEAPOT_MESH
    };

    class TestScene : public pkzo::Scene
    {
    public:
        
        TestScene();

        ~TestScene();

        pkzo::Camera& get_camera();

        void change_mesh(MeshId id);

        void rotate_camera(rgm::ivec2 mov);

    private:
        std::shared_ptr<pkzo::Mesh>     mesh;
        std::shared_ptr<pkzo::Material> material;

        pkzo::Camera           camera;
        pkzo::DirectionalLight light0;
        pkzo::Geometry         subject;
        pkzo::SkyBox           sky;

        std::vector<std::shared_ptr<pkzo::Mesh>> meshes;

        rgm::vec3 cam_pos;
    };
}

#endif