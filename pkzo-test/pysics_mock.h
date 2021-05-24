//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublpkzonse, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notpkzo and this permission notpkzo shall be included in
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


#include <gmock/gmock.h>
#include <pkzo/physics.h>

namespace pkzo::test
{
    class MockRigidBody : public pkzo::physics::RigidBody
    {
    public:
        MOCK_METHOD(glm::mat4, get_transform, (), (const, noexcept, override));

        MOCK_METHOD(void, set_mass, (KiloGramm value), (noexcept, override));
        MOCK_METHOD(KiloGramm, get_mass, (), (const, noexcept, override));

        MOCK_METHOD(void, set_friction, (float value), (noexcept, override));
        MOCK_METHOD(float, get_friction, (), (const, noexcept, override));

        MOCK_METHOD(void, set_rolling_friction, (float value), (noexcept, override));
        MOCK_METHOD(float, get_rolling_friction, (), (const, noexcept, override));

        MOCK_METHOD(void, set_linear_factor, (const glm::vec3& value), (noexcept, override));
        MOCK_METHOD(glm::vec3, get_linear_factor, (), (const, noexcept, override));

        MOCK_METHOD(void, set_angular_factor, (const glm::vec3& value), (noexcept, override));
        MOCK_METHOD(glm::vec3, get_angular_factor, (), (const, noexcept, override));

        MOCK_METHOD(glm::vec3, get_linear_velocity, (), (const, noexcept, override));
        MOCK_METHOD(glm::vec3, get_angular_velocity, (), (const, noexcept, override));

        MOCK_METHOD(void, apply_impulse, (const glm::vec3& value), (noexcept, override));
        MOCK_METHOD(void, apply_force, (const glm::vec3& value), (noexcept, override));

        MOCK_METHOD(rsig::signal<>&, get_move_signal, (), (noexcept, override));
        MOCK_METHOD(rsig::signal<pkzo::physics::RigidBody&>&, get_collide_signal, (), (noexcept, override));

        MOCK_METHOD(void, set_user_data, (const std::any& value), (noexcept, override));
        MOCK_METHOD(const std::any&, get_user_data, (), (const, noexcept, override));;
    };

    class MockWorld : public pkzo::physics::World
    {
    public:
        MOCK_METHOD(void, set_gravity, (const glm::vec3& value), (noexcept, override));
        MOCK_METHOD(glm::vec3, get_gravity, (), (const, noexcept, override));

        MOCK_METHOD(std::shared_ptr<pkzo::physics::RigidBody>, add_box, (const glm::mat4& transform, const glm::vec3& size, KiloGramm mass), (noexcept, override));
        MOCK_METHOD(std::shared_ptr<pkzo::physics::RigidBody>, add_capsule, (const glm::mat4& transform, float diameter, float height, KiloGramm mass), (noexcept, override));
        MOCK_METHOD(std::shared_ptr<pkzo::physics::RigidBody>, add_sphere, (const glm::mat4& transform, float diameter, KiloGramm mass), (noexcept, override));
        MOCK_METHOD(std::shared_ptr<pkzo::physics::RigidBody>, add_static_mesh, (const glm::mat4& transform, std::shared_ptr<Mesh> mesh) , (noexcept, override));

        MOCK_METHOD(void, remove_body, (const std::shared_ptr<pkzo::physics::RigidBody>& body), (noexcept, override));

        MOCK_METHOD(std::optional<pkzo::physics::TestResult>, test_ray, (const glm::vec3& start, const glm::vec3& end), (const, noexcept, override));
        MOCK_METHOD(std::optional<pkzo::physics::TestResult>, test_sphere_sweep, (const glm::vec3& start, const glm::vec3& end, float radius), (const, noexcept, override));

        MOCK_METHOD(void, update, (std::chrono::milliseconds dt), (noexcept, override));
    };
}