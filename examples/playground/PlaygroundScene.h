
#ifndef _PLAYGROUND_SCENE_H_
#define _PLAYGROUND_SCENE_H_

#include <pkzo/Scene.h>
#include <pkzo/SkyBox.h>
#include <pkzo/AmbientLight.h>
#include <pkzo/DirectionalLight.h>
#include <pkzo/BoxGeometry.h>

namespace pg
{
    class PlaygroundEngine;

    class PlaygroundScene : public pkzo::Scene
    {
    public:
        
        PlaygroundScene(PlaygroundEngine& engine);

        ~PlaygroundScene();

    private:
        pkzo::SkyBox           sky;
        pkzo::AmbientLight     ambient_light;
        pkzo::DirectionalLight sun_light;                
        pkzo::BoxGeometry      box;
    };
}

#endif
