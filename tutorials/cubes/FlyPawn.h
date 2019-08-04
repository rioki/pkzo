// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_FLY_PAWN_H_
#define _CUBES_FLY_PAWN_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class FlyPawn : public pkzo::SceneNodeGroup
    {
    public:
        FlyPawn(pkzo::Engine& engine);

        std::shared_ptr<pkzo::Camera> get_camera() const;

        void update(float dt) /*override*/;

    private:
        bool rotating = false;
        glm::vec2 rotation = {0.0f, 0.0f};
        bool move_fore  = false;
        bool move_back  = false;
        bool move_left  = false;
        bool move_right = false;
        bool move_up    = false;
        bool move_down  = false;
        float speed = 1.4f;

        std::shared_ptr<pkzo::Camera> camera;

        glm::vec3 get_target_velocity() const;
    };
}

#endif
