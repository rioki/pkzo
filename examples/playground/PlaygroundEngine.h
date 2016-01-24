
#ifndef _PLAYGROUND_ENGINE_H_
#define _PLAYGROUND_ENGINE_H_

#include <pkzo/Engine.h>

namespace pg
{
    class Pawn;

    class PlaygroundEngine : public pkzo::Engine
    {
    public:
        
        PlaygroundEngine();

        ~PlaygroundEngine();

    private:
        Pawn* pawn;
    };
}

#endif
