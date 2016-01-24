
#include "BoxGeometry.h"

#include "Mesh.h"

namespace pkzo
{
    std::weak_ptr<Mesh> BoxGeometry::shared_mesh;

    BoxGeometry::BoxGeometry()
    {        
        if (shared_mesh.expired())
        {
            mesh = std::shared_ptr<Mesh>(new Mesh);
            mesh->create_box(Vector3(1, 1, 1));

            shared_mesh = mesh;            
        }
        else
        {
            std::shared_ptr<Mesh> sm = shared_mesh.lock();
            mesh = sm;
        }        
    }

    BoxGeometry::~BoxGeometry()
    {
    }
}