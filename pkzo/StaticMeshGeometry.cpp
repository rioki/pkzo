
#include "StaticMeshGeometry.h"

#include "SceneRenderer.h"

namespace pkzo
{
    StaticMeshGeometry::StaticMeshGeometry() {}

    StaticMeshGeometry::~StaticMeshGeometry() {}

    void StaticMeshGeometry::set_mesh(std::shared_ptr<Mesh> value) 
    {
        mesh = value;
    }

    std::shared_ptr<Mesh> StaticMeshGeometry::get_mesh() const
    {
        return mesh;
    }
}