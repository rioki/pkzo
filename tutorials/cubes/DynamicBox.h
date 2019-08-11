// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_DYNAMIC_BOX_H_
#define _CUBES_DYNAMIC_BOX_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class DynamicBox : public pkzo::Body
    {
    public:
        DynamicBox(const glm::vec3& size, float mass, const std::shared_ptr<pkzo::Material>& material);
    };
}

#endif
