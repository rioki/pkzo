
#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

namespace teapot
{
    class TeapotEngine;

    class CameraController
    {
    public:
        
        CameraController(TeapotEngine& engine);

        ~CameraController();

    private:
        TeapotEngine& engine;

        float distance;
        float alpha;
        float beta;

        void update();
    };
}

#endif
