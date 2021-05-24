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
#include "Geometry.h"

#include "Scene.h"
#include "Pipeline.h"
#include "Mesh.h"
#include "Body.h"
#include "Material.h"
#include "physics.h"

using namespace pkzo::mass_literals;

namespace pkzo
{
    Geometry::Geometry() noexcept = default;

    Geometry::Geometry(const glm::mat4& transform) noexcept
    : SceneNode(transform) {}

    Geometry::Geometry(const glm::mat4& transform, const std::shared_ptr<Material>& m) noexcept
    : SceneNode(transform), material(m) {}

    void Geometry::set_visible(bool value) noexcept
    {
        visible = value;
        // TODO if active add or remove from graphics
    }

    bool Geometry::get_visible() const noexcept
    {
        return visible;
    }

    void Geometry::set_collidable(bool value) noexcept
    {
        collidable = value;
        // TODO if active add or remove from physics
    }

    bool Geometry::get_collidable() const noexcept
    {
        return collidable;
    }

    void Geometry::set_material(const std::shared_ptr<Material>& value) noexcept
    {
        material = value;
    }

    const std::shared_ptr<Material>& Geometry::get_material() const noexcept
    {
        return material;
    }

    void Geometry::update(std::chrono::milliseconds dt) noexcept
    {
        SceneNode::update(dt);
        DBG_ASSERT(pipeline);
        DBG_ASSERT(pipeline_handle != 0);
        pipeline->update_geometry(pipeline_handle, get_world_transform());
    }

    void Geometry::on_attach_scene(Scene* scene) noexcept
    {
        SceneNode::on_attach_scene(scene);
        pipeline = scene->get_render_pipeline();
        pipeline_handle = pipeline->add_geometry(get_world_transform(), get_mesh(), get_material()->to_parameters());

        if (collidable)
        {
            auto body = find_elder<Body>();
            if (body == nullptr)
            {
                auto physics = scene->get_physics();
                assert(physics);
                rigid_body = create_rigid_body(physics, 0kg);
                rigid_body->set_user_data(static_cast<SceneNode*>(this));
            }
        }
    }

    void Geometry::on_detach_scene() noexcept
    {
        pipeline->remove_geometry(pipeline_handle);
        pipeline        = nullptr;
        pipeline_handle = 0;

        if (rigid_body)
        {
            auto physics = get_scene()->get_physics();
            assert(physics);
            physics->remove_body(rigid_body);
            rigid_body = nullptr;
        }

        SceneNode::on_detach_scene();
    }
}