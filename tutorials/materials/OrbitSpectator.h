// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _MATERIALS_ORBIT_SPECTATOR_H_
#define _MATERIALS_ORBIT_SPECTATOR_H_

#include <pkzo/pkzo.h>

namespace mats
{
    class OrbitSpectator : public pkzo::Camera
    {
    public:
        OrbitSpectator(pkzo::Engine& engine, const glm::vec3& pivot);

        void set_pivot(const glm::vec3& value);

        const glm::vec3& get_pivor() const;

    private:
        glm::vec3 pivot;
        glm::vec3 coords = {0.0f, 0.0f, 10.0f};
        bool orbiting = false;
        bool panning = false;

        void update();
    };
}

#endif


