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
#include "Text.h"

#include "Screen.h"

namespace ice
{
    Text::Text(const glm::mat3& tr, const std::string& te, const std::shared_ptr<Font>& f) noexcept
    : Text(tr, te, f, glm::vec4(1.0f)) {}

    Text::Text(const glm::mat3& transform, const std::string& t, const std::shared_ptr<Font>& f, const glm::vec4& c) noexcept
    : ScreenNode(transform), text(t), font(f), color(c)
    {
        assert(font);
        on_move([this] () {
            if (render_handle)
            {
                render_handle->set_transform(get_world_transform());
            }
        });
    }

    glm::vec2 Text::get_size() const noexcept
    {
        assert(font);
        if (texture)
        {
            return glm::vec2(texture->get_size());
        }
        else
        {
            return glm::vec2(font->estimate(text));
        }
    }

    void Text::set_text(const std::string& value) noexcept
    {
        text = value;
        if (font)
        {
            texture = font->render(text);
        }
        if (render_handle)
        {
            render_handle->set_texture(texture);
            render_handle->set_size(glm::vec2(texture->get_size()));
        }
    }

    const std::string& Text::get_text() const noexcept
    {
        return text;
    }

    void Text::set_color(const glm::vec4& value) noexcept
    {
        color = value;
        if (render_handle)
        {
            render_handle->set_color(color);
        }
    }

    const glm::vec4& Text::get_color() const noexcept
    {
        return color;
    }

    void Text::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        assert(font);
        font = value;
        if (font)
        {
            texture = font->render(text);
        }
        if (render_handle)
        {
            render_handle->set_texture(texture);
            render_handle->set_size(glm::vec2(texture->get_size()));
        }
    }

    const std::shared_ptr<Font>& Text::get_font() const noexcept
    {
        return font;
    }

    void Text::activate()
    {
        assert(render_handle == nullptr);

        if (font)
        {
            texture = font->render(text);
        }

        auto screen = get_root();
        assert(screen != nullptr);
        auto renderer = screen->get_renderer();
        if (auto renderer = screen->get_renderer())
        {
            render_handle = renderer->add_rectangle(get_world_transform(), get_size(), color, texture);
        }
    }

    void Text::deactivate()
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