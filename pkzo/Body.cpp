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
#include "Body.h"

#include "Scene.h"
#include "Geometry.h"

namespace pkzo
{
    Body::Body(const glm::mat4& transform, KiloGramm m)
    : SceneNodeGroup(transform), mass(m) {}

    Body::~Body() = default;

    void Body::set_mass(KiloGramm value) noexcept
    {
        mass = value;
        if (rigid_body)
        {
            rigid_body->set_mass(value);
        }
    }

    KiloGramm Body::get_mass() const noexcept
    {
        return mass;
    }

    void Body::set_friction(float value) noexcept
    {
        friction = value;
        if (rigid_body)
        {
            rigid_body->set_friction(value);
        }
    }

    float Body::get_friction() const noexcept
    {
        return friction;
    }

    void Body::set_rolling_friction(float value) noexcept
    {
        rolling_friction = value;
        if (rigid_body)
        {
            rigid_body->set_rolling_friction(value);
        }
    }

    float Body::get_rolling_friction() const noexcept
    {
        return rolling_friction;
    }

    void Body::set_linear_factor(const glm::vec3& value) noexcept
    {
        linear_factor = value;
        if (rigid_body)
        {
            rigid_body->set_linear_factor(value);
        }
    }

    glm::vec3 Body::get_linear_factor() const noexcept
    {
        return linear_factor;
    }

    void Body::set_angular_factor(const glm::vec3& value) noexcept
    {
        angular_factor = value;
        if (rigid_body)
        {
            rigid_body->set_angular_factor(value);
        }
    }

    glm::vec3 Body::get_angular_factor() const noexcept
    {
        return angular_factor;
    }

    void Body::apply_impulse(const glm::vec3& value) noexcept
    {
        if (rigid_body)
        {
            rigid_body->apply_impulse(value);
        }
    }

    void Body::apply_force(const glm::vec3& value) noexcept
    {
        if (rigid_body)
        {
            rigid_body->apply_force(value);
        }
    }

    glm::vec3 Body::get_linear_velocity() const noexcept
    {
        if (rigid_body)
        {
            return rigid_body->get_linear_velocity();
        }
        else
        {
            return glm::vec3(0.0f);
        }
    }

    glm::vec3 Body::get_angular_velocity() const noexcept
    {
        if (rigid_body)
        {
            return rigid_body->get_angular_velocity();
        }
        else
        {
            return glm::vec3(0.0f);
        }
    }

    void Body::on_attach_scene(Scene* scene) noexcept
    {
        SceneNodeGroup::on_attach_scene(scene);

        auto physics = scene->get_physics();

        auto geoms = find_nodes<Geometry>();
        auto i = std::remove_if(begin(geoms), end(geoms), [] (auto& geom) { return geom->get_collidable() == false; });
        geoms.erase(i, end(geoms));
        if (!geoms.empty())
        {
            assert(geoms.size() == 1); // currently only one geometry per body is supported
            rigid_body = geoms[0]->create_rigid_body(physics, mass);
            offset = geoms[0]->get_world_transform() * glm::inverse(get_world_transform());
            rigid_body->set_friction(friction);
            rigid_body->set_rolling_friction(rolling_friction);
            rigid_body->set_linear_factor(linear_factor);
            rigid_body->set_angular_factor(angular_factor);
            rigid_body->get_move_signal().connect([this] () {
                set_transform(rigid_body->get_transform() * glm::inverse(offset));
            });
            rigid_body->set_user_data(static_cast<SceneNode*>(this));
        }
    }

    void Body::on_detach_scene() noexcept
    {
        auto scene = get_scene();
        assert(scene != nullptr);

        auto physics = scene->get_physics();
        physics->remove_body(rigid_body);
        rigid_body = nullptr;

        SceneNodeGroup::on_detach_scene();
    }
}
