// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "PhysicsSimulation.h"

#include <map>
#include <memory>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>
// yes... we need to extend include path...
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

#include <pkzo/Mesh.h>

namespace pkzo
{
    using pkzo::Mesh;
    class BulletDebugDraw;

    class PKZO_EXPORT BulletPhysicsSimulation : public PhysicsSimulation
    {
    public:
        BulletPhysicsSimulation();

        ~BulletPhysicsSimulation();

        void add(Body* body) override;
        void remove(Body* body) override;

        void add(Ghost* ghost) override;
        void remove(Ghost* ghost) override;

        void add(Geometry* geometry) override;
        void remove(Geometry* geometry) override;

        void set_gravity(const glm::vec3& value) override;
        glm::vec3 get_gravity() const override;

        std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const override;
        std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const override;

        void update(float dt) override;

        void enable_debug_render(SceneRenderer& renderer) override;
        void disable_debug_render() override;

    private:
        std::unique_ptr<btBroadphaseInterface>    broadphase;
        std::unique_ptr<btCollisionConfiguration> collisionConfiguration;
        std::unique_ptr<btCollisionDispatcher>    dispatcher;
        std::unique_ptr<btConstraintSolver>       solver;
        std::unique_ptr<btDynamicsWorld>          world;
        std::unique_ptr<BulletDebugDraw>          debug_draw;

        struct StaticHandle
        {
            std::unique_ptr<btMotionState>     state;
            std::unique_ptr<btCollisionShape>  shape;
            std::unique_ptr<btRigidBody>       body;
        };
        struct DynamicHandle : public StaticHandle
        {
            Body*     node;
            glm::mat4 offset;

            void sync();
        };
        struct GhostHandle
        {
            std::unique_ptr<btCollisionShape>  shape;
            std::unique_ptr<btGhostObject>     object;
        };

        struct Ingest
        {
            Body*     body     = nullptr;
            Ghost*    ghost    = nullptr;
            Geometry* geometry = nullptr;
        };
        std::vector<Ingest> ingest;

        std::map<Geometry*, StaticHandle>  static_bodies;
        std::map<Body*,     DynamicHandle> dynamic_bodies;
        std::map<Ghost*,    GhostHandle>   ghosts;

        // We want strong refs to Mesh here, because btStridingMeshInterface uses that memory.
        std::map<std::shared_ptr<Mesh>, std::unique_ptr<btStridingMeshInterface>, std::owner_less<>> mesh_data;

        void handle_ingest();

        void add_dynamic_body(Body* body, Geometry* geometry);
        void add_ghost(Ghost* ghost, Geometry* geometry);
        void add_static_geometry(Geometry* geometry);
        std::unique_ptr<btCollisionShape> make_collision_shape(Geometry* geometry);
        btStridingMeshInterface* create_bullet_mesh(std::shared_ptr<Mesh> mesh);
    };
}
