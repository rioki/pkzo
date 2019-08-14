// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_DYNAMIC_CAPSULE_H_
#define _CUBES_DYNAMIC_CAPSULE_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class DynamicCapsule : public pkzo::Body
    {
    public:
        DynamicCapsule(float diameter, float height, float mass, const std::shared_ptr<pkzo::Material>& material);
    };
}

#endif
