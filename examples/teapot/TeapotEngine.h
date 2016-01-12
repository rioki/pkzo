
#ifndef _TEAPOT_ENGINE_H_
#define _TEAPOT_ENGINE_H_

#include <pkzo/Engine.h>

namespace teapot
{
    class CameraController;

    class TeapotEngine : public pkzo::Engine
    {
    public:
        TeapotEngine();

        ~TeapotEngine();

    private:
        CameraController* controller;
    };
}

#endif
