// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _CUBES_STATIC_MESH_H_
#define _CUBES_STATIC_MESH_H_

#include <pkzo/pkzo.h>

namespace cubes
{
    class StaticMesh : public pkzo::SceneNodeGroup
    {
    public:
        StaticMesh(const std::shared_ptr<pkzo::Mesh> mesh, const std::shared_ptr<pkzo::Material>& material);
    };
}

#endif
