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
#include "SceneNodeGroup.h"

#include <bullet/btBulletDynamicsCommon.h>
#include "Mass.h"
#include "fwd.h"

namespace pkzo
{
    class PKZO_EXPORT Body : public SceneNodeGroup
    {
    public:
        Body(const glm::mat4& transform, KiloGramm mass);
        ~Body();

        void set_mass(KiloGramm value) noexcept;
        KiloGramm get_mass() const noexcept;

        void set_friction(float value) noexcept;
        float get_friction() const noexcept;

        void set_rolling_friction(float value) noexcept;
        float get_rolling_friction() const noexcept;

        void set_linear_factor(const glm::vec3& value) noexcept;
        glm::vec3 get_linear_factor() const noexcept;

        void set_angular_factor(const glm::vec3& value) noexcept;
        glm::vec3 get_angular_factor() const noexcept;

        void apply_impulse(const glm::vec3& value) noexcept;
        void apply_force(const glm::vec3& value) noexcept;

        glm::vec3 get_linear_velocity() const noexcept;
        glm::vec3 get_angular_velocity() const noexcept;

    protected:
        void on_attach_scene(Scene* scene) noexcept override;
        void on_detach_scene() noexcept override;

    private:
        KiloGramm mass             = {1.0f};
        float     friction         = 0.0f;
        float     rolling_friction = 0.0f;
        glm::vec3 linear_factor    = glm::vec3(1.0f);
        glm::vec3 angular_factor   = glm::vec3(1.0f);

        std::shared_ptr<physics::RigidBody> rigid_body;
        glm::mat4 offset;
    };
}
