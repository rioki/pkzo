
#ifndef _ATRIUM_ENGINE_H_
#define _ATRIUM_ENGINE_H_

#include <pkzo/Engine.h>

namespace atrium
{
    class Pawn;

    class AtriumEngine : public pkzo::Engine
    {
    public:
        AtriumEngine();
        ~AtriumEngine();

    private:
        Pawn* pawn;
    };
}

#endif
