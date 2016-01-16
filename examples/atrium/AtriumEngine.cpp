
#include "AtriumEngine.h"

#include "AtriumScene.h"
#include "Pawn.h"

namespace atrium
{
    AtriumEngine::AtriumEngine()
    : Engine("pkzo Atrium"), pawn(nullptr) 
    {
        pawn = new Pawn(*this);

        switch_scene(new AtriumScene(get_library()));

        on(pkzo::Engine::CHANGE_SCENE, [this] () {
            pkzo::Scene& scene = get_scene();
            scene.add_node(*pawn);
        });
    }

    AtriumEngine::~AtriumEngine()
    {
        delete pawn;
    }
}