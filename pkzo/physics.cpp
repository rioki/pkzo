//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "physics.h"

#include <bullet/btBulletDynamicsCommon.h>

namespace pkzo::physics
{
    using namespace mass_literals;

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

    class BulletRigidBody : public RigidBody
    {
    public:
        BulletRigidBody(std::shared_ptr<btMotionState> _state, std::shared_ptr<btCollisionShape> _shape, std::shared_ptr<btRigidBody> _body) noexcept
            : state(_state), shape(_shape), body(_body)
        {
            assert(state);
            assert(shape);
            assert(body);
            body->setUserPointer(this);
        }

        glm::mat4 get_transform() const noexcept override
        {
            assert(body);
            return to_glm(body->getWorldTransform());
        }

        void set_mass(KiloGramm value) noexcept override
        {
            assert(body);
            auto interia = btVector3{0, 0, 0};
            if (value > 0kg)
            {
                assert(shape);
                shape->calculateLocalInertia(btScalar(value.count()), interia);
            }
            body->setMassProps(btScalar(value.count()), interia);
        }

        KiloGramm get_mass() const noexcept override
        {
            return KiloGramm(body->getMass());
        }

        void set_friction(float value) noexcept override
        {
            assert(body);
            body->setFriction(value);
        }

        float get_friction() const noexcept override
        {
            assert(body);
            return body->getFriction();
        }

        void set_rolling_friction(float value) noexcept override
        {
            assert(body);
            body->setRollingFriction(value);
        }

        float get_rolling_friction() const noexcept override
        {
            assert(body);
            return body->getRollingFriction();
        }

        void set_linear_factor(const glm::vec3& value) noexcept override
        {
            assert(body);
            body->setLinearFactor(to_bt(value));
        }

        glm::vec3 get_linear_factor() const noexcept override
        {
            assert(body);
            return to_glm(body->getLinearFactor());
        }

        void set_angular_factor(const glm::vec3& value) noexcept override
        {
            assert(body);
            body->setAngularFactor(to_bt(value));
        }

        glm::vec3 get_angular_factor() const noexcept override
        {
            assert(body);
            return to_glm(body->getAngularFactor());
        }

        glm::vec3 get_linear_velocity() const noexcept override
        {
            assert(body);
            return to_glm(body->getLinearVelocity());
        }

        glm::vec3 get_angular_velocity() const noexcept override
        {
            assert(body);
            return to_glm(body->getAngularVelocity());
        }

        void apply_impulse(const glm::vec3& value) noexcept override
        {
            assert(body);
            body->applyCentralImpulse(to_bt(value));
            body->activate();
        }

        void apply_force(const glm::vec3& value) noexcept override
        {
            assert(body);
            body->applyCentralForce(to_bt(value));
            body->activate();
        }

        rsig::signal<>& get_move_signal() noexcept override
        {
            return move_signal;
        }

        rsig::signal<RigidBody&>& get_collide_signal() noexcept override
        {
            return collide_signal;
        }

        void set_user_data(const std::any& value) noexcept override
        {
            user_data = value;
        }

        const std::any& get_user_data() const noexcept override
        {
            return user_data;
        }

        void sync()
        {
            // if it is active, it probably moved
            if (body->isActive())
            {
                move_signal.emit();
            }
        }

    private:
        std::shared_ptr<btMotionState>    state;
        std::shared_ptr<btCollisionShape> shape;
        std::shared_ptr<btRigidBody>      body;

        rsig::signal<>           move_signal;
        rsig::signal<RigidBody&> collide_signal;

        std::any user_data;

        friend class BulletWorld;
    };

    class BulletWorld : public World
    {
    public:
        BulletWorld()
        {
            broadphase             = std::make_unique<btDbvtBroadphase>();
            collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
            dispatcher             = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
            solver                 = std::make_unique<btSequentialImpulseConstraintSolver>();

            world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get());
            world->setGravity({0.0f, 0.0f, 0.0f});
        }

        ~BulletWorld()
        {
            for (auto& body : bodies)
            {
                assert(body);
                assert(body->body);
                world->removeRigidBody(body->body.get());
            }
        }

        void set_gravity(const glm::vec3& value) noexcept override
        {
            assert(world);
            world->setGravity(to_bt(value));
        }

        glm::vec3 get_gravity() const noexcept override
        {
            assert(world);
            return to_glm(world->getGravity());
        }

        std::shared_ptr<RigidBody> add_box(const glm::mat4& transform, const glm::vec3& size, KiloGramm mass) noexcept override
        {
            auto shape = std::make_shared<btBoxShape>(to_bt(size * 0.5f));
            return add_body(transform, mass, shape);
        }

        std::shared_ptr<RigidBody> add_capsule(const glm::mat4& transform, float diameter, float height, KiloGramm mass) noexcept override
        {
            auto shape = std::make_shared<btCapsuleShapeZ>(diameter * 0.5f, height - diameter);
            return add_body(transform, mass, shape);
        }

        std::shared_ptr<RigidBody> add_sphere(const glm::mat4& transform, float diameter, KiloGramm mass) noexcept override
        {
            auto shape = std::make_shared<btSphereShape>(diameter / 2.0f);
            return add_body(transform, mass, shape);
        }

        std::shared_ptr<RigidBody> add_static_mesh(const glm::mat4& transform, std::shared_ptr<Mesh> mesh) noexcept override
        {
            auto shape = std::make_shared<btBvhTriangleMeshShape>(create_bullet_mesh(mesh).get(), true);
            return add_body(transform, 0kg, shape);
        }

        void remove_body(const std::shared_ptr<RigidBody>& b) noexcept override
        {
            auto body = std::dynamic_pointer_cast<BulletRigidBody>(b);
            assert(body);

            auto i = find(begin(bodies), end(bodies), body);
            assert(i != end(bodies));
            bodies.erase(i);

            assert(body->body);
            world->removeRigidBody(body->body.get());
        }

        std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const noexcept override
        {
            btCollisionWorld::ClosestRayResultCallback callback(to_bt(start), to_bt(end));
            world->rayTest(to_bt(start), to_bt(end), callback);
            if (callback.hasHit())
            {
                auto body = reinterpret_cast<RigidBody*>(callback.m_collisionObject->getUserPointer());
                assert(body != nullptr);
                return TestResult{
                    body->shared_from_this(),
                    to_glm(callback.m_hitPointWorld),
                    to_glm(callback.m_hitNormalWorld)
                };
            }
            else
            {
                return std::nullopt;
            }
        }

        std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const noexcept override
        {
            auto sphere = btSphereShape{radius};
            btCollisionWorld::ClosestConvexResultCallback callback(to_bt(start), to_bt(end));
            world->convexSweepTest(&sphere, btTransform{NO_ROTATION, to_bt(start)}, btTransform{NO_ROTATION, to_bt(end)}, callback);
            if (callback.hasHit())
            {
                auto body = reinterpret_cast<RigidBody*>(callback.m_hitCollisionObject->getUserPointer());
                assert(body != nullptr);
                return TestResult{
                    body->shared_from_this(),
                    to_glm(callback.m_hitPointWorld),
                    to_glm(callback.m_hitNormalWorld)
                };
            }
            else
            {
                return std::nullopt;
            }
        }

        void World::update(std::chrono::milliseconds dt) noexcept override
        {
            assert(world);
            world->stepSimulation(std::chrono::duration<float>(dt).count());

            for (auto& body : bodies)
            {
                body->sync();
            }
        }

    private:
        std::unique_ptr<btBroadphaseInterface>    broadphase;
        std::unique_ptr<btCollisionConfiguration> collisionConfiguration;
        std::unique_ptr<btCollisionDispatcher>    dispatcher;
        std::unique_ptr<btConstraintSolver>       solver;
        std::unique_ptr<btDynamicsWorld>          world;

        std::list<std::shared_ptr<BulletRigidBody>> bodies;
        std::map<std::shared_ptr<Mesh>, std::shared_ptr<btStridingMeshInterface>> mesh_data;

        std::shared_ptr<RigidBody> add_body(const glm::mat4& transform, KiloGramm mass, std::shared_ptr<btCollisionShape> shape) noexcept
        {
            auto state   = std::make_shared<btDefaultMotionState>(to_bt(transform));
            auto interia = btVector3{0, 0, 0};
            if (mass > 0kg)
            {
                shape->calculateLocalInertia(btScalar(mass.count()), interia);
            }

            auto body = std::make_shared<btRigidBody>(btScalar(mass.count()), state.get(), shape.get(), interia);

            if (mass == 0kg)
            {
                body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
                body->setActivationState(DISABLE_SIMULATION);
            }

            world->addRigidBody(body.get());

            auto rb = std::make_shared<BulletRigidBody>(state, shape, body);
            bodies.push_back(rb);
            return rb;
        }

        std::shared_ptr<btStridingMeshInterface> create_bullet_mesh(std::shared_ptr<Mesh> mesh)
        {
            assert(mesh);
            auto i = mesh_data.find(mesh);
            if (i != end(mesh_data))
            {
                return i->second;
            }
            else
            {
                auto bullet_mesh = std::make_shared<btTriangleIndexVertexArray>();
                btIndexedMesh indexedMeshData = {};
                indexedMeshData.m_triangleIndexStride = sizeof(unsigned) * 3;
                indexedMeshData.m_vertexStride        = sizeof(glm::vec3);
                indexedMeshData.m_vertexType          = PHY_ScalarType::PHY_FLOAT;
                indexedMeshData.m_numTriangles        = static_cast<int>(mesh->get_faces().size());
                indexedMeshData.m_numVertices         = static_cast<int>(mesh->get_vertices().size());
                indexedMeshData.m_triangleIndexBase   = reinterpret_cast<const unsigned char*>(glm::value_ptr(mesh->get_faces().front()));
                indexedMeshData.m_vertexBase          = reinterpret_cast<const unsigned char*>(glm::value_ptr(mesh->get_vertices().front()));
                bullet_mesh->addIndexedMesh(indexedMeshData);

                mesh_data[mesh] = bullet_mesh;
                return bullet_mesh;
            }
        }
    };

    std::unique_ptr<World> World::create()
    {
        return std::make_unique<BulletWorld>();
    }
}