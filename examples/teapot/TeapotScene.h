
#ifndef _TEAPOT_SCENE_H_
#define _TEAPOT_SCENE_H_

#include <pkzo/Scene.h>
#include <pkzo/Camera.h>
#include <pkzo/SkyBox.h>
#include <pkzo/AmbientLight.h>
#include <pkzo/DirectionalLight.h>
#include <pkzo/Geometry.h>
#include <pkzo/Library.h>

namespace teapot
{
    class TeapotScene : public pkzo::Scene
    {
    public:
        
        TeapotScene(pkzo::Library& library);

        ~TeapotScene();

    private:
        pkzo::SkyBox           sky;        
        pkzo::AmbientLight     light0;
        pkzo::DirectionalLight light1;
        pkzo::Geometry         teapot;        
        pkzo::Camera           camera;
    };

}

#endif
