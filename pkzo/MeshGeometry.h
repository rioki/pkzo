// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MESH_GEOMETRY_H_
#define _PKZO_MESH_GEOMETRY_H_

#include "Geometry.h"

namespace pkzo
{
    class Mesh;

    //! Static Mesh Geometry
    class PKZO_EXPORT MeshGeometry : public Geometry
    {
    public:
        MeshGeometry(std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material>& material);

        ~MeshGeometry();

        //! Change the mesh of the geometry.
        void set_mesh(std::shared_ptr<Mesh> value);

        //! Get the mesh of the geometry.
        std::shared_ptr<Mesh> get_mesh() const;

        void enqueue(RenderQueue& queue) const override;

    private:
        std::shared_ptr<Mesh> mesh;
    };
}

#endif
