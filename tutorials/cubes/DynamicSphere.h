// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_DYNAMIC_SPHERE_H_
#define _CUBES_DYNAMIC_SPHERE_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class DynamicSphere : public pkzo::Body
    {
    public:
        DynamicSphere(float diameter, float mass, const std::shared_ptr<pkzo::Material>& material);
    };
}

#endif
