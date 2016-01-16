
#include "Pawn.h"

#include <pkzo/Mouse.h>
#include <pkzo/Keyboard.h>

using pkzo::Vector3;
using pkzo::Quaternion;

namespace atrium
{
    Pawn::Pawn(pkzo::Engine& e) 
    : engine(e), speed(0.05), invmouse(false), pitch(0), yaw(0)
    {
        // TMP 
        set_position(pkzo::Vector3(-5.0f, 0, 2));

        camera.set_orientation(Quaternion::axis_angle(-90.0f, Vector3(0, 0, 1)) * 
                               Quaternion::axis_angle(90.0f, Vector3(1, 0, 0)));
        add_node(camera);

        pkzo::Mouse& mouse = engine.get_mouse();

        mouse.on(pkzo::Mouse::MOVE, [this] (unsigned int x, unsigned int y, int dx, int dy) {
            
            pkzo::Mouse& mouse = engine.get_mouse();
            if (mouse.is_pressed(1))
            {
                if (invmouse)
                {
                    pitch -= dy;
                }
                else
                {
                    pitch += dy;
                }
                yaw  -= dx;
            }
        });
    }

    Pawn::~Pawn() {}

    void Pawn::update(float t, float dt)
    {
        pkzo::Keyboard& keyboard = engine.get_keyboard();

        SceneNodeGroup::update(t, dt);

        Quaternion o = Quaternion::axis_angle(yaw, Vector3(0, 0, 1)) * 
                       Quaternion::axis_angle(pitch, Vector3(0, 1, 0));
        
        Vector3 p = get_position();
        Vector3 x = pkzo::transform(o, Vector3(1, 0, 0));
        Vector3 y = pkzo::transform(o, Vector3(0, 1, 0));

        // TOOD key binding 
        if (keyboard.is_pressed(pkzo::KEY_W))
        {
            p += x * speed * dt;
        }
        if (keyboard.is_pressed(pkzo::KEY_S))
        {
            p -= x * speed * dt;
        }
        if (keyboard.is_pressed(pkzo::KEY_A))
        {
            p += y * speed * dt;
        }
        if (keyboard.is_pressed(pkzo::KEY_D))
        {
            p -= y * speed * dt;
        }


        //pkzo::Vector3 p = pkzo::transform(o, pkzo::Vector3(0, 0, 10));

        set_orientation(o);
        set_position(p);
    }
}
