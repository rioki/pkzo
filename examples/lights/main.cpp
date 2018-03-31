// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <pkzo/pkzo.h>
#include <pkzo3d/pkzo3d.h>

rgm::quat orient(float pitch, float yaw)
{
    return rgm::axis_angle<float>(rgm::vec3(0, 0, 1), yaw) * 
          rgm::axis_angle<float>(rgm::vec3(1, 0, 0), pitch);           
}

rgm::vec3 move_fwd(const rgm::vec3& pos, const rgm::quat& orient, float dt)
{
   rgm::vec3 fwd = rgm::transform(orient, rgm::vec3(0, 0, -1));
    return pos + fwd * dt;
}

rgm::vec3 move_bk(const rgm::vec3& pos, const rgm::quat& orient, float dt)
{
   rgm::vec3 fwd = rgm::transform(orient, rgm::vec3(0, 0, 1));
    return pos + fwd * dt;
}

rgm::vec3 move_l(const rgm::vec3& pos, const rgm::quat& orient, float dt)
{
   rgm::vec3 fwd = rgm::transform(orient, rgm::vec3(-1, 0, 0));
    return pos + fwd * dt;
}

rgm::vec3 move_r(const rgm::vec3& pos, const rgm::quat& orient, float dt)
{
   rgm::vec3 fwd = rgm::transform(orient, rgm::vec3(1, 0, 0));
    return pos + fwd * dt;
}

int main(int argc, char* argv[])
{    
    float pitch   = 90.0;
    float yaw     = 0.0;
    float lx      = 0.0;

    pkzo::EventLoop loop;

    pkzo::SceneRenderer renderer;

    pkzo::Scene scene;
    
    auto shpere = pkzo::load_mesh("../assets/meshes/Teapot.ply");
    auto white  = pkzo::load_material("../assets/materials/White.jmn");

    pkzo::MeshGeometry sphere0;
    sphere0.set_material(white);
    sphere0.set_mesh(shpere);
    sphere0.set_position(rgm::vec3(-5, 0, 1));
    sphere0.set_orientation(rgm::axis_angle<float>(rgm::vec3(0, 0, 1), 90.0));
    scene.add_entity(sphere0);

    pkzo::MeshGeometry sphere1;
    sphere1.set_material(white);
    sphere1.set_mesh(shpere);
    sphere1.set_position(rgm::vec3(0, 0, 1));
    scene.add_entity(sphere1);

    pkzo::MeshGeometry sphere2;
    sphere2.set_material(white);
    sphere2.set_mesh(shpere);
    sphere2.set_position(rgm::vec3(5, 0, 1));
    sphere2.set_orientation(rgm::axis_angle<float>(rgm::vec3(0, 1, 0), 90.0));
    scene.add_entity(sphere2);

    pkzo::BoxGeometry ground;
    ground.set_material(white);
    ground.set_size(rgm::vec3(100, 100, 0.1));
    scene.add_entity(ground);

    pkzo::DirectionalLight light0;
    scene.add_entity(light0);

    pkzo::SkyBox sky;
    sky.set_cubemap(pkzo::load_cubemap("../assets/textures/Morning_XPos.jpg", "../assets/textures/Morning_XNeg.jpg",
                                       "../assets/textures/Morning_YPos.jpg", "../assets/textures/Morning_YNeg.jpg",
                                       "../assets/textures/Morning_ZPos.jpg", "../assets/textures/Morning_ZNeg.jpg"));
    scene.add_entity(sky);

    pkzo::Camera camera;
    camera.set_position(rgm::vec3(0, -10, 1));
    camera.set_orientation(orient(pitch, yaw));
    scene.add_entity(camera);

    auto window = loop.open_window(1280, 768);
    window->on_draw([&] () {              
        scene.draw(renderer, window->get_aspect(), camera);
    });
    window->on_close([&] () {                   
        loop.stop();
    });

    auto keyboard = loop.get_keyboard();                   
    keyboard->on_key_press([&] (pkzo::Key key) {
        if (key == pkzo::KEY_ESCAPE)           
        {                                      
            loop.stop();                  
        }
    });    

    auto mouse = loop.get_mouse();
    mouse->on_move([&] (rgm::ivec2& mov, rgm::ivec2& pos) {        
        if (mouse->is_pressed(1))
        {
            yaw   += mov[0];
            pitch += mov[1];
            
            camera.set_orientation(orient(pitch, yaw));
        }
    });

    loop.on_tick([&] () {
        if (keyboard->is_pressed(pkzo::KEY_W))
        {
            auto p = move_fwd(camera.get_position(), camera.get_orientation(), 0.1);
            camera.set_position(p);
        }
        if (keyboard->is_pressed(pkzo::KEY_S))
        {
            auto p = move_bk(camera.get_position(), camera.get_orientation(), 0.1);
            camera.set_position(p);
        }
        if (keyboard->is_pressed(pkzo::KEY_A))
        {
            auto p = move_l(camera.get_position(), camera.get_orientation(), 0.1);
            camera.set_position(p);
        }
        if (keyboard->is_pressed(pkzo::KEY_D))
        {
            auto p = move_r(camera.get_position(), camera.get_orientation(), 0.1);
            camera.set_position(p);
        }

        lx += 0.5;
        light0.set_orientation(rgm::axis_angle<float>(rgm::vec3(1, 0, 0), lx));
    });

    loop.run();

    return 0;
}
