// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "Visual.h"

#include "SceneNode.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"

namespace pkzo
{
    std::shared_ptr<Material> Visual::get_default_material() noexcept
    {
        static auto cache = std::weak_ptr<Material>();

        auto mat = cache.lock();
        if (mat)
        {
            return mat;
        }

        mat = make_simple_material(rgb(0xff00dc));
        cache = mat;
        return mat;
    }

    Visual::Visual(const glm::mat4& transform, const std::shared_ptr<const Mesh>& _mesh, const std::shared_ptr<const Material>& _material, const glm::vec3& _local_scale) noexcept
    : SceneNode(transform), mesh(_mesh), material(_material), local_scale(_local_scale)
    {
        on_move([this] ()
        {
            if (renderer)
            {
                const auto t = glm::scale(get_world_transform(), local_scale);
                renderer->update_geometry_transform(render_handle, t);
            }
        });
    }

    const std::shared_ptr<const Mesh>& Visual::get_mesh() const noexcept
    {
        return mesh;
    }

    void Visual::set_material(const std::shared_ptr<const Material>& value)
    {
        material = value;
        if (renderer)
        {
            renderer->update_geometry_material(render_handle, material);
        }
    }

    const std::shared_ptr<const Material>& Visual::get_material() const noexcept
    {
        return material;
    }

    void Visual::activate()
    {
        assert(renderer == nullptr);
        auto scene = get_root();
        assert(scene != nullptr);
        if (renderer = scene->get_renderer())
        {
            const auto t = glm::scale(get_world_transform(), local_scale);
            render_handle = renderer->add_geometry(t, mesh, material);
        }
    }

    void Visual::deactivate()
    {
        if (renderer != nullptr)
        {
            renderer->remove_geometry(render_handle);
            renderer      = nullptr;
            render_handle = 0;
        }
    }

    void Visual::set_mesh(const std::shared_ptr<const Mesh>& value)
    {
        mesh = value;
        if (renderer)
        {
            renderer->update_geometry_mesh(render_handle, mesh);
        }
    }

    const glm::vec3& Visual::get_local_scale() const noexcept
    {
        return local_scale;
    }

    void Visual::set_local_scale(const glm::vec3& value) noexcept
    {
        local_scale = value;
        if (renderer)
        {
            const auto t = glm::scale(get_world_transform(), local_scale);
            renderer->update_geometry_transform(render_handle, t);
        }
    }
}
