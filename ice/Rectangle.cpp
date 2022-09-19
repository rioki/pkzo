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

#include "Screen.h"

namespace ice
{
    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const glm::vec4& _color) noexcept
    : Rectangle(_transform, _size, _color, nullptr) {}

    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const std::shared_ptr<Texture>& _texture) noexcept
    : Rectangle(_transform, _size, glm::vec4(1.0f), _texture) {}

    Rectangle::Rectangle(const glm::mat3& _transform, const glm::vec2& _size, const glm::vec4& _color, const std::shared_ptr<Texture>& _texture) noexcept
    : ScreenNode(_transform), size(_size), color(_color), texture(_texture)
    {
        on_move([this] () {
            if (render_handle)
            {
                render_handle->set_transform(get_world_transform());
            }
        });
    }

    void Rectangle::set_size(const glm::vec2& value) noexcept
    {
        size = value;
        if (render_handle)
        {
            render_handle->set_size(size);
        }
    }

    const glm::vec2& Rectangle::get_size() const noexcept
    {
        return size;
    }

    void Rectangle::set_color(const glm::vec4& value) noexcept
    {
        color = value;
        if (render_handle)
        {
            render_handle->set_color(color);
        }
    }

    const glm::vec4& Rectangle::get_color() const noexcept
    {
        return color;
    }

    void Rectangle::set_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        texture = value;
        if (render_handle)
        {
            render_handle->set_texture(texture);
        }
    }

    const std::shared_ptr<Texture>& Rectangle::get_texture() const noexcept
    {
        return texture;
    }

    void Rectangle::activate()
    {
        assert(render_handle == nullptr);

        auto screen = get_root();
        assert(screen != nullptr);
        if (auto renderer = screen->get_renderer())
        {
            render_handle = renderer->add_rectangle(get_world_transform(), size, color, texture);
        }
    }

    void Rectangle::deactivate()
    {
        if (render_handle != nullptr)
        {
            auto screen = get_root();
            assert(screen != nullptr);
            auto renderer = screen->get_renderer();
            assert(renderer != nullptr);
            renderer->remove_geometry(render_handle);
            render_handle = nullptr;
        }
    }
}
