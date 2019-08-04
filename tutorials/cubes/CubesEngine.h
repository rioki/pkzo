// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_ENGINE_H_
#define _CUBES_ENGINE_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class CubesEngine : public pkzo::Engine
    {
    public:
        CubesEngine();

    private:
        std::shared_ptr<pkzo::Scene> create_scene();
    };
}

#endif
