
#include "CameraController.h"

#include <pkzo/Mouse.h>
#include <pkzo/Scene.h>
#include <pkzo/Camera.h>

#include "TeapotEngine.h"

namespace teapot
{
    CameraController::CameraController(TeapotEngine& e) 
    : engine(e), distance(10), alpha(180), beta(80)
    {
        pkzo::Mouse& mouse = engine.get_mouse();

        mouse.on(pkzo::Mouse::MOVE, [this] (unsigned int x, unsigned int y, int dx, int dy) {
            
            pkzo::Mouse& mouse = engine.get_mouse();
            if (mouse.is_pressed(1))
            {
                alpha -= dx;
                beta  -= dy;
                update();
            }
        });

        engine.on(pkzo::Engine::CHANGE_SCENE, [this] () {
            update();
        });        
    }

    CameraController::~CameraController() {}

    void CameraController::update()
    {
        if (engine.has_scene())
        {
            pkzo::Scene& scene = engine.get_scene();

            std::vector<pkzo::Camera*> cameras = scene.get_nodes<pkzo::Camera>();
            if (cameras.size() == 1)
            {
                pkzo::Quaternion o = pkzo::Quaternion::axis_angle(alpha, pkzo::Vector3(0, 0, 1)) * 
                                     pkzo::Quaternion::axis_angle(beta, pkzo::Vector3(1, 0, 0));
                
                pkzo::Vector3 p = pkzo::transform(o, pkzo::Vector3(0, 0, 10));

                cameras[0]->set_orientation(o);
                cameras[0]->set_position(p);
            }
        }
    }
}
