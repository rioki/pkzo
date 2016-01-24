
#ifndef _PAWN_H_
#define _PAWN_H_

#include <pkzo/SceneNodeGroup.h>
#include <pkzo/Camera.h>
#include <pkzo/Engine.h>

namespace pg
{
    class Pawn : public pkzo::SceneNodeGroup
    {
    public:
        
        Pawn(pkzo::Engine& engine);

        ~Pawn();

        void update(float t, float dt) override;

    private:
        pkzo::Engine& engine;
        
        float speed;
        bool  invmouse;
        float pitch;
        float yaw;

        pkzo::Camera camera;
    };
}

#endif
