// Ice Engine
// Copyright 2022 Sean Farrell
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
#include "Rectangle.h"

#include "glm_2d.h"
#include "glm_utils.h"
#include "Screen.h"
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

namespace ice
{
    Rectangle::Rectangle()
    : Rectangle(glm::mat4(1.0f), glm::vec2(15.0f), glm::vec4(1.0f), nullptr) {}

    Rectangle::Rectangle(const glm::mat3& transform)
    : Rectangle(transform, glm::vec2(15.0f), glm::vec4(1.0f), nullptr) {}

    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const glm::vec4& _color) noexcept
    : Rectangle(_transform, _size, _color, nullptr) {}

    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const std::shared_ptr<Texture>& _texture) noexcept
    : Rectangle(_transform, _size, glm::vec4(1.0f), _texture) {}

    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const glm::vec4& _color, const std::shared_ptr<Texture>& _texture) noexcept
    : ScreenNode(_transform), size(_size), color(_color), texture(_texture)
    {
        on_move([this] () {
            if (renderer)
            {
                renderer->update_geometry_transform(render_handle, glm::scale(to3d(get_aligned_transform()), glm::vec3(size, 1.0f)));
            }
        });
    }

    void Rectangle::set_size(const glm::vec2& value) noexcept
    {
        size = value;
        if (renderer)
        {
            renderer->update_geometry_transform(render_handle, glm::scale(to3d(get_aligned_transform()), glm::vec3(size, 1.0f)));
        }
    }

    const glm::vec2& Rectangle::get_size() const noexcept
    {
        return size;
    }

    void Rectangle::set_color(const glm::vec4& value) noexcept
    {
        color = value;
        if (renderer)
        {
            renderer->update_geometry_material(render_handle, make_simple_material(color, texture));
        }
    }

    const glm::vec4& Rectangle::get_color() const noexcept
    {
        return color;
    }

    void Rectangle::set_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        texture = value;
        if (renderer)
        {
            renderer->update_geometry_material(render_handle, make_simple_material(color, texture));
        }
    }

    const std::shared_ptr<Texture>& Rectangle::get_texture() const noexcept
    {
        return texture;
    }

    auto get_unit_rect()
    {
        static std::weak_ptr<Mesh> cache;

        auto mesh = cache.lock();
        if (mesh)
        {
            return mesh;
        }

        mesh = make_rectangle_mesh(glm::vec2(1.0f));
        cache = mesh;
        return mesh;
    }

    void Rectangle::activate()
    {
        assert(renderer == nullptr);
        auto scene = get_root();
        assert(scene != nullptr);
        if (renderer = scene->get_renderer())
        {
            const auto transform = glm::scale(to3d(get_aligned_transform()), glm::vec3(size, 1.0f));
            const auto mesh      = get_unit_rect();
            const auto material  = make_simple_material(color, texture);
            render_handle = renderer->add_geometry(transform, mesh, material);
        }
    }

    void Rectangle::deactivate()
    {
        if (renderer != nullptr)
        {
            auto screen = get_root();
            assert(screen != nullptr);
            auto renderer = screen->get_renderer();
            assert(renderer != nullptr);
            renderer->remove_geometry(render_handle);
            renderer = nullptr;
        }
    }

    // Special case handling; if the size is the texture size,
    // and has no rotation, we assume a pefect pixel alignmen is desired.
    // Nudge the transform by less than a pixel to match the texture to
    // the pixel grid.
    // Note we assume 1.0f is one pixel.
    glm::mat3 Rectangle::get_aligned_transform() const noexcept
    {
        if (texture == nullptr)
        {
            return get_world_transform();
        }

        // size != texture->get_size()
        if (!glm::close(glm::vec2(texture->get_size()), size, 1e-4f))
        {
            return get_world_transform();
        }

        auto transform = get_world_transform();

        // no rotation
        if (!glm::close(glm::mat2(transform), glm::mat2(1.0f), 1e-4f))
        {
            return get_world_transform();
        }

        auto half_size = size / 2.0f;
        auto top_right = glm::transform(transform, half_size);
        auto top_right_cor = glm::round(top_right);
        auto diff = top_right - top_right_cor;
        return glm::translate(transform, diff);
    }
}
