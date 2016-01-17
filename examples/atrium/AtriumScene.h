
#ifndef _ATRIUM_SCENE_H_
#define _ATRIUM_SCENE_H_

#include <pkzo/Scene.h>
#include <pkzo/Library.h>
#include <pkzo/Geometry.h>
#include <pkzo/AmbientLight.h>
#include <pkzo/DirectionalLight.h>
#include <pkzo/SkyBox.h>

namespace atrium
{
    class AtriumScene : public pkzo::Scene
    {
    public:
        AtriumScene(pkzo::Library& lib);
        ~AtriumScene();

    private:
        pkzo::AmbientLight           ambient_light;
        pkzo::DirectionalLight       sun_light;        
        pkzo::SkyBox                 sky;
        std::vector<pkzo::Geometry*> static_objets;
        std::vector<pkzo::Light*>    lights;
    };
}

#endif
