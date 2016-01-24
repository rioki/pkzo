
#ifndef _PKZO_STATIC_MESH_GEOMETRY_H_
#define _PKZO_STATIC_MESH_GEOMETRY_H_

#include "Geometry.h"

namespace pkzo
{
    class PKZO_EXPORT StaticMeshGeometry : public Geometry
    {
    public:
        StaticMeshGeometry();
        
        ~StaticMeshGeometry();

        void set_mesh(std::shared_ptr<Mesh> value);

        std::shared_ptr<Mesh> get_mesh() const;

        void enqueue(SceneRenderer & renderer) const override;

    private:
        std::shared_ptr<Mesh> mesh;
    };
}

#endif
