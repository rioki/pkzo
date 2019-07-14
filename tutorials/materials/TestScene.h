// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _MATERIALS_TEST_SCENE_H_
#define _MATERIALS_TEST_SCENE_H_

#include <pkzo/pkzo.h>

namespace mats
{
    class TestScene : public pkzo::Scene
    {
    public:
        TestScene();

        std::shared_ptr<pkzo::Camera> get_camera() const;

    private:
        std::shared_ptr<pkzo::Camera> camera;
    };
}

#endif
