#include "PlaygroundEngine.h"

#include "PlaygroundScene.h"
#include "Pawn.h"

namespace pg
{
    PlaygroundEngine::PlaygroundEngine()
    : Engine("pkzo Playground"), pawn(nullptr)  
    {
        pawn = new Pawn(*this);

        switch_scene(new PlaygroundScene(*this));

        on(pkzo::Engine::CHANGE_SCENE, [this] () {
            pkzo::Scene& scene = get_scene();
            scene.add_node(*pawn);
        });
    }

    PlaygroundEngine::~PlaygroundEngine() 
    {
        delete pawn;
    }
}