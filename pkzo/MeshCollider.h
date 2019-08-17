// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MESH_COLLIDER_H_
#define _PKZO_MESH_COLLIDER_H_

#include "Collider.h"

class btTriangleIndexVertexArray;
class btBvhTriangleMeshShape;

namespace pkzo
{
    class Mesh;

    //! Mesh Collider
    class PKZO_EXPORT MeshCollider : public Collider
    {
    public:
        //! Create mesh collider.
        MeshCollider(const std::shared_ptr<Mesh>& mesh);
        ~MeshCollider();
        //! Get the mesh..
        const std::shared_ptr<Mesh>& get_mesh() const;

    protected:
        std::shared_ptr<btCollisionShape> get_collision_shape() override;

    private:
        std::shared_ptr<Mesh>                       mesh;
        std::unique_ptr<btTriangleIndexVertexArray> bt_mesh_data;
        std::shared_ptr<btBvhTriangleMeshShape>     collision_shape;
    };
}

#endif
