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

#pragma once

#include "config.h"

#include <memory>
#include <chrono>
#include <optional>
#include <any>
#include <glm/fwd.hpp>

#include "rsig.h"
#include "Mass.h"
#include "Mesh.h"

namespace pkzo::physics
{
    class PKZO_EXPORT RigidBody : public std::enable_shared_from_this<RigidBody>
    {
    public:
        RigidBody() = default;
        RigidBody(const RigidBody&) = delete;
        virtual ~RigidBody() = default;
        RigidBody& operator = (const RigidBody&) = delete;

        virtual glm::mat4 get_transform() const noexcept = 0;

        virtual void set_mass(KiloGramm value) noexcept = 0;
        virtual KiloGramm get_mass() const noexcept = 0;

        virtual void set_friction(float value) noexcept = 0;
        virtual float get_friction() const noexcept = 0;

        virtual void set_rolling_friction(float value) noexcept = 0;
        virtual float get_rolling_friction() const noexcept = 0;

        virtual void set_linear_factor(const glm::vec3& value) noexcept = 0;
        virtual glm::vec3 get_linear_factor() const noexcept = 0;

        virtual void set_angular_factor(const glm::vec3& value) noexcept = 0;
        virtual glm::vec3 get_angular_factor() const noexcept = 0;

        virtual glm::vec3 get_linear_velocity() const noexcept = 0;
        virtual glm::vec3 get_angular_velocity() const noexcept = 0;

        virtual void apply_impulse(const glm::vec3& value) noexcept = 0;
        virtual void apply_force(const glm::vec3& value) noexcept = 0;

        virtual rsig::signal<>& get_move_signal() noexcept = 0;
        virtual rsig::signal<RigidBody&>& get_collide_signal() noexcept = 0;

        virtual void set_user_data(const std::any& value) noexcept = 0;
        virtual const std::any& get_user_data() const noexcept = 0;
    };

    struct TestResult
    {
        std::shared_ptr<RigidBody> body;
        glm::vec3 position;
        glm::vec3 normal;
    };

    class PKZO_EXPORT World
    {
    public:
        static std::unique_ptr<World> create();

        World() = default;
        World(const World&) = delete;
        virtual ~World() = default;
        World& operator = (const World&) = delete;

        virtual void set_gravity(const glm::vec3& value) noexcept = 0;
        virtual glm::vec3 get_gravity() const noexcept = 0;

        virtual std::shared_ptr<RigidBody> add_box(const glm::mat4& transform, const glm::vec3& size, KiloGramm mass) noexcept = 0;
        virtual std::shared_ptr<RigidBody> add_capsule(const glm::mat4& transform, float diameter, float height, KiloGramm mass) noexcept = 0;
        virtual std::shared_ptr<RigidBody> add_sphere(const glm::mat4& transform, float diameter, KiloGramm mass) noexcept = 0;
        virtual std::shared_ptr<RigidBody> add_static_mesh(const glm::mat4& transform, std::shared_ptr<Mesh> mesh) noexcept = 0;

        virtual void remove_body(const std::shared_ptr<RigidBody>& body) noexcept = 0;

        virtual std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const noexcept = 0;
        virtual std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const noexcept = 0;

        virtual void update(std::chrono::milliseconds dt) noexcept = 0;
    };
}
