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

#include "BulletPhysicsSimulation.h"

#include <pkzo/debug.h>
#include <glm/gtc/type_ptr.hpp>

#include "Body.h"
#include "Ghost.h"
#include "Geometry.h"
#include "BoxGeometry.h"
#include "MeshGeometry.h"
#include "SphereGeometry.h"
#include "CylinderGeometry.h"
#include "SceneRenderer.h"

namespace pkzo3d
{
    using pkzo::check;

    const auto NO_ROTATION = btQuaternion{0.0f, 0.0f, 0.0f, 1.0f};

    inline btTransform to_bt(const glm::mat4& trans)
    {
        auto result = btTransform{};
        result.setFromOpenGLMatrix(glm::value_ptr(trans));
        return result;
    }

    inline glm::mat4 to_glm(const btTransform& trans)
    {
        auto result = glm::mat4(1.0f);
        trans.getOpenGLMatrix(glm::value_ptr(result));
        return result;
    }

    inline btVector3 to_bt(const glm::vec3& vec)
    {
        return {vec.x, vec.y, vec.z};
    }

    inline glm::vec3 to_glm(const btVector3& vec)
    {
        return {vec[0], vec[1], vec[2]};
    }

    void BulletPhysicsSimulation::DynamicHandle::sync()
    {
        if (body->isActive())
        {
            node->set_transform(to_glm(body->getWorldTransform()) * offset);
        }
    }

    BulletPhysicsSimulation::BulletPhysicsSimulation()
    {
        broadphase             = std::make_unique<btDbvtBroadphase>();
        collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
        dispatcher             = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
        solver                 = std::make_unique<btSequentialImpulseConstraintSolver>();

        world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get());
        world->setGravity({0.0f, 0.0f, 0.0f});
    }

    BulletPhysicsSimulation::~BulletPhysicsSimulation()
    {
        check(dynamic_bodies.empty());
        check(static_bodies.empty());
    }

    void BulletPhysicsSimulation::add(Body* body)
    {
        check(body != nullptr);
        check(std::find_if(begin(ingest), end(ingest), [&] (const auto& in) { return in.body == body; }) == end(ingest));
        check(dynamic_bodies.find(body) == end(dynamic_bodies));

        ingest.push_back({
            .body = body
        });
    }

    void BulletPhysicsSimulation::remove(Body* body)
    {
        auto i = dynamic_bodies.find(body);
        if (i != end(dynamic_bodies))
        {
            world->removeRigidBody(i->second.body.get());
            dynamic_bodies.erase(i);
        }
        else
        {
            auto j = std::find_if(begin(ingest), end(ingest), [&] (const auto& env) { return env.body == body; } );
            if (j != end(ingest))
            {
                ingest.erase(j);
            }
        }
    }

    void BulletPhysicsSimulation::add(Ghost* ghost)
    {
        check(ghost != nullptr);
        check(std::find_if(begin(ingest), end(ingest), [&] (const auto& in) { return in.ghost == ghost; }) == end(ingest));
        check(ghosts.find(ghost) == end(ghosts));

        ingest.push_back({
            .ghost = ghost
        });
    }

    void BulletPhysicsSimulation::remove(Ghost* ghost)
    {
        auto i = ghosts.find(ghost);
        if (i != end(ghosts))
        {
            world->removeCollisionObject(i->second.object.get());
            ghosts.erase(i);
        }
        else
        {
            auto j = std::find_if(begin(ingest), end(ingest), [&] (const auto& env) { return env.ghost == ghost; } );
            if (j != end(ingest))
            {
                ingest.erase(j);
            }
        }
    }

    void BulletPhysicsSimulation::add(Geometry* geometry)
    {
        check(geometry != nullptr);
        if (auto body = geometry->find_ancestor<Body>())
        {
            auto i = std::find_if(begin(ingest), end(ingest), [&] (const auto& in) { return in.body == body; });
            check(i != end(ingest));
            check(i->geometry == nullptr, "Only one Gemoetry per Body is allowed.");
            i->geometry = geometry;
        }
        else if (auto ghost = geometry->find_ancestor<Ghost>())
        {
            auto i = std::find_if(begin(ingest), end(ingest), [&] (const auto& in) { return in.ghost == ghost; });
            check(i != end(ingest));
            check(i->geometry == nullptr, "Only one Gemoetry per Ghost is allowed.");
            i->geometry = geometry;
        }
        else
        {
            ingest.push_back({
                .geometry = geometry
            });
        }
    }

    void BulletPhysicsSimulation::remove(Geometry* geometry)
    {
        check(geometry);

        // We can't check if the given geometry does have a body,
        // becuase it may already be semi destructed and only a mere group.
        // thus we just check if it is static. If it was dynamic the cleanup
        // of the Body already did the work.

        auto i = static_bodies.find(geometry);
        if (i != end(static_bodies))
        {
            world->removeRigidBody(i->second.body.get());
            static_bodies.erase(i);
        }
        else
        {
            auto j = std::find_if(begin(ingest), end(ingest), [&] (const auto& env) { return env.geometry == geometry; } );
            if (j != end(ingest))
            {
                ingest.erase(j);
            }
        }
    }

    void BulletPhysicsSimulation::set_gravity(const glm::vec3& value)
    {
        check(world);
        world->setGravity(to_bt(value));
    }

    glm::vec3 BulletPhysicsSimulation::get_gravity() const
    {
        check(world);
        return to_glm(world->getGravity());
    }

    std::optional<TestResult> BulletPhysicsSimulation::test_ray(const glm::vec3& start, const glm::vec3& end) const
    {
        auto callback = btCollisionWorld::ClosestRayResultCallback(to_bt(start), to_bt(end));
        world->rayTest(to_bt(start), to_bt(end), callback);
        if (callback.hasHit())
        {
            auto node = reinterpret_cast<Node*>(callback.m_collisionObject->getUserPointer());
            return TestResult{
                node,
                to_glm(callback.m_hitPointWorld),
                to_glm(callback.m_hitNormalWorld)
            };
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<TestResult> BulletPhysicsSimulation::test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const
    {
        auto sphere   = btSphereShape{radius};
        auto callback = btCollisionWorld::ClosestConvexResultCallback(to_bt(start), to_bt(end));
        world->convexSweepTest(&sphere, btTransform{NO_ROTATION, to_bt(start)}, btTransform{NO_ROTATION, to_bt(end)}, callback);
        if (callback.hasHit())
        {
            auto node = reinterpret_cast<Node*>(callback.m_hitCollisionObject->getUserPointer());
            return TestResult{
                node,
                to_glm(callback.m_hitPointWorld),
                to_glm(callback.m_hitNormalWorld)
            };
        }
        else
        {
            return std::nullopt;
        }
    }

    void BulletPhysicsSimulation::update(float dt)
    {
        check(world);

        handle_ingest();

        // TODO estimate subsetps
        world->stepSimulation(dt);

        for (auto& [body, handle] : dynamic_bodies)
        {
            handle.sync();
        }

        if (debug_draw)
        {
            world->debugDrawWorld();
        }
    }

    class BulletDebugDraw : public btIDebugDraw
    {
    public:
        BulletDebugDraw(SceneRenderer& renderer)
        : renderer(renderer) {}

        void drawLine(const btVector3& a, const btVector3& b, const btVector3& color) override
        {
            drawLine(a, b, color, color);
        }

        void drawLine(const btVector3& a, const btVector3& b, const btVector3& ca, const btVector3& cb) override
        {
            renderer.add_debug_line(to_glm(a), to_glm(b), glm::vec4(to_glm(ca), 1.0f), glm::vec4(to_glm(cb), 1.0f));
        }

        void drawContactPoint(const btVector3& p, const btVector3& n, btScalar distance, int lifeTime, const btVector3& color) override
        {
            const btVector3 q = p + n * distance;
            drawLine(p, q, color);
        }

        void draw3dText(const btVector3& pos, const char* text) override {}

        void reportErrorWarning(const char* warning) override {}

        void setDebugMode(int value) override
        {
            mode = value;
        }
        int getDebugMode() const override
        {
            return mode;
        }

    private:
         SceneRenderer& renderer;
         int mode = 0;
    };

    void BulletPhysicsSimulation::enable_debug_render(SceneRenderer& renderer)
    {
        check(world);

        debug_draw = std::make_unique<BulletDebugDraw>(renderer);
        debug_draw->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb);

        world->setDebugDrawer(debug_draw.get());
    }

    void BulletPhysicsSimulation::disable_debug_render()
    {
        check(world);

        world->setDebugDrawer(nullptr);
        debug_draw = nullptr;
    }

    void BulletPhysicsSimulation::handle_ingest()
    {
        for (auto& item : ingest)
        {
            if (item.body != nullptr)
            {
                check(item.ghost == nullptr);
                add_dynamic_body(item.body, item.geometry);
            }
            else if (item.ghost != nullptr)
            {
                add_ghost(item.ghost, item.geometry);
            }
            else
            {
                add_static_geometry(item.geometry);
            }
        }
        ingest.clear();
    }

    void BulletPhysicsSimulation::add_dynamic_body(Body* body, Geometry* geometry)
    {
        // TODO handle multiple geoms
        check(body != nullptr);
        check(geometry != nullptr);
        // TODO if mesh -> make convex hull
        // TODO geometry offset
        auto shape = make_collision_shape(geometry);

        auto offset = glm::inverse(geometry->get_global_transform()) * body->get_global_transform();

        auto state = std::make_unique<btDefaultMotionState>(to_bt(geometry->get_global_transform()));

        auto mass = body->get_mass();
        check(mass > 0.0f);

        auto interia = btVector3{0, 0, 0};
        shape->calculateLocalInertia(mass, interia);

        auto btbody = std::make_unique<btRigidBody>(mass, state.get(), shape.get(), interia);
        btbody->setUserPointer(body);

        world->addRigidBody(btbody.get());

        dynamic_bodies.insert({body, {std::move(state), std::move(shape), std::move(btbody), body, offset}});
    }

    void BulletPhysicsSimulation::add_ghost(Ghost* ghost, Geometry* geometry)
    {
        check(ghost != nullptr);
        check(geometry != nullptr);

        auto shape = make_collision_shape(geometry);

        auto btghost = std::make_unique<btGhostObject>();
        btghost->setCollisionShape(shape.get());
        btghost->setWorldTransform(to_bt(geometry->get_global_transform()));
        btghost->setUserPointer(ghost);

        world->addCollisionObject(btghost.get());

        ghosts.insert({ghost, {std::move(shape), std::move(btghost)}});
    }

    void BulletPhysicsSimulation::add_static_geometry(Geometry* geometry)
    {
        auto shape = make_collision_shape(geometry);

        auto state   = std::make_unique<btDefaultMotionState>(to_bt(geometry->get_global_transform()));
        auto interia = btVector3{0, 0, 0};

        auto body = std::make_unique<btRigidBody>(0.0f, state.get(), shape.get(), interia);
        body->setUserPointer(geometry);

        body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
        body->setActivationState(DISABLE_SIMULATION);

        world->addRigidBody(body.get());

        static_bodies.insert({geometry, {std::move(state), std::move(shape), std::move(body)}});
    }

    std::unique_ptr<btCollisionShape> BulletPhysicsSimulation::make_collision_shape(Geometry* geometry)
    {
        if (auto box_geom = dynamic_cast<BoxGeometry*>(geometry))
        {
            return std::make_unique<btBoxShape>(to_bt(box_geom->get_size() * 0.5f));
        }
        else if (auto sphere_geom = dynamic_cast<SphereGeometry*>(geometry))
        {
            return std::make_unique<btSphereShape>(sphere_geom->get_diameter() * 0.5f);
        }
        else if (auto cylinder_geom = dynamic_cast<CylinderGeometry*>(geometry))
        {
            auto bounds = cylinder_geom->get_bounds();
            return std::make_unique<btCylinderShapeZ>(to_bt(bounds.get_size() * 0.5f));
        }
        else if (auto mesh_geom = dynamic_cast<MeshGeometry*>(geometry))
        {
            return std::make_unique<btBvhTriangleMeshShape>(create_bullet_mesh(mesh_geom->get_mesh()), true);
        }
        else
        {
            throw std::logic_error("Unknown Geometry");
        }
    }

    btStridingMeshInterface* BulletPhysicsSimulation::create_bullet_mesh(std::shared_ptr<Mesh> mesh)
    {
        check(mesh);
        auto i = mesh_data.find(mesh);
        if (i != end(mesh_data))
        {
            return i->second.get();
        }
        else
        {
            auto bullet_mesh = std::make_unique<btTriangleIndexVertexArray>();
            btIndexedMesh indexedMeshData = {};
            indexedMeshData.m_triangleIndexStride = sizeof(unsigned) * 3;
            indexedMeshData.m_vertexStride        = sizeof(glm::vec3);
            indexedMeshData.m_vertexType          = PHY_ScalarType::PHY_FLOAT;
            indexedMeshData.m_numTriangles        = static_cast<int>(mesh->get_faces().size());
            indexedMeshData.m_numVertices         = static_cast<int>(mesh->get_vertexes().size());
            indexedMeshData.m_triangleIndexBase   = reinterpret_cast<const unsigned char*>(glm::value_ptr(mesh->get_faces().front()));
            indexedMeshData.m_vertexBase          = reinterpret_cast<const unsigned char*>(glm::value_ptr(mesh->get_vertexes().front()));
            bullet_mesh->addIndexedMesh(indexedMeshData);

            auto ptr = bullet_mesh.get();
            mesh_data.insert({mesh, std::move(bullet_mesh)});
            return ptr;
        }
    }
}
