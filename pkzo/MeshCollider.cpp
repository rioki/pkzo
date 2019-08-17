// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "MeshCollider.h"

#include <bullet/btBulletDynamicsCommon.h>
#include "btutils.h"
#include "Mesh.h"
#include "Engine.h"
#include "PhysicSystem.h"

namespace pkzo
{
    MeshCollider::MeshCollider(const std::shared_ptr<Mesh>& m)
    : mesh(m) {}

    MeshCollider::~MeshCollider() = default;

    const std::shared_ptr<Mesh>& MeshCollider::get_mesh() const
    {
        return mesh;
    }

    std::shared_ptr<btCollisionShape> MeshCollider::get_collision_shape()
    {
        if (collision_shape == nullptr)
        {
            // TODO cache the shape and reuse it
            const auto& indexes  = mesh->get_faces();
            const auto& vertexes = mesh->get_vertexes();

            bt_mesh_data = std::make_unique<btTriangleIndexVertexArray>();

            btIndexedMesh bt_index_mesh;
            bt_index_mesh.m_indexType           = PHY_INTEGER;
            bt_index_mesh.m_numTriangles        = indexes.size();
            bt_index_mesh.m_triangleIndexBase   = reinterpret_cast<const unsigned char*>(indexes.data());
            bt_index_mesh.m_triangleIndexStride = sizeof(glm::uvec3);
            bt_index_mesh.m_vertexType          = PHY_FLOAT;
            bt_index_mesh.m_numVertices         = vertexes.size();
            bt_index_mesh.m_vertexBase          = reinterpret_cast<const unsigned char*>(vertexes.data());
            bt_index_mesh.m_vertexStride        = sizeof(glm::vec3);

            bt_mesh_data->addIndexedMesh(bt_index_mesh);

            collision_shape = std::make_shared<btBvhTriangleMeshShape>(bt_mesh_data.get(), true, true);
        }
        return collision_shape;
    }
}
