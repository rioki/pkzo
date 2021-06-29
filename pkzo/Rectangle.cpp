//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
#include "Rectangle.h"

#include "Scene.h"
#include "Pipeline.h"
#include "Material.h"
#include "Mesh.h"

namespace pkzo
{
    Rectangle::Rectangle() noexcept = default;

    Rectangle::Rectangle(const glm::vec2& s, const std::shared_ptr<Material>& m) noexcept
    : size(s), material(m)
    {
        DBG_ASSERT(material);
    }

    Rectangle::Rectangle(const glm::mat4& transform, const glm::vec2& s, const std::shared_ptr<Material>& m) noexcept
    : SceneNode(transform), size(s), material(m)
    {
        DBG_ASSERT(material);
    }

    Rectangle::~Rectangle() = default;

    void Rectangle::set_size(const glm::vec2& value) noexcept
    {
        size = value;
        dirty = true;
    }

    const glm::vec2& Rectangle::get_size() const noexcept
    {
        return size;
    }

    void Rectangle::set_material(const std::shared_ptr<Material>& value)
    {
        material = value;
        dirty = true;
    }

    const std::shared_ptr<Material>& Rectangle::get_material() const
    {
        return material;
    }

    void Rectangle::update(std::chrono::milliseconds dt) noexcept
    {
        SceneNode::update(dt);
        DBG_ASSERT(pipeline);
        DBG_ASSERT(pipeline_handle != 0);
        pipeline->update_geometry(pipeline_handle, get_world_transform());
        if (dirty)
        {
            pipeline->update_geometry(pipeline_handle, make_rectangle(size));
            pipeline->update_geometry(pipeline_handle, material->to_parameters());
            dirty = false;
        }
    }

    void Rectangle::on_attach_scene(Scene* scene) noexcept
    {
        SceneNode::on_attach_scene(scene);
        pipeline = scene->get_render_pipeline();
        pipeline_handle = pipeline->add_geometry(get_world_transform(), make_rectangle(size), material->to_parameters());
    }

    void Rectangle::on_detach_scene() noexcept
    {
        pipeline->remove_geometry(pipeline_handle);
        pipeline        = nullptr;
        pipeline_handle = 0;
        SceneNode::on_detach_scene();
    }
}
