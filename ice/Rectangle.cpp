// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

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

        auto screen = get_screen();
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
            auto screen = get_screen();
            assert(screen != nullptr);
            auto renderer = screen->get_renderer();
            assert(renderer != nullptr);
            renderer->remove_geometry(render_handle);
            render_handle = nullptr;
        }
    }
}
