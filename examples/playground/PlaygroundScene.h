
#ifndef _PLAYGROUND_SCENE_H_
#define _PLAYGROUND_SCENE_H_

#include <pkzo/Scene.h>
#include <pkzo/SkyBox.h>

namespace pg
{
    class PlaygroundEngine;

    class PlaygroundScene : public pkzo::Scene
    {
    public:
        
        PlaygroundScene(PlaygroundEngine& engine);

        ~PlaygroundScene();

    private:
        pkzo::SkyBox sky;
    };
}

#endif
