// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_STATIC_BOX_H_
#define _CUBES_STATIC_BOX_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class StaticBox : public pkzo::SceneNodeGroup
    {
    public:
        StaticBox(const glm::vec3& size, const std::shared_ptr<pkzo::Material>& material);
    };
}

#endif
