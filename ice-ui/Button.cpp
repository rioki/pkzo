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
#include "Button.h"

namespace ice::ui
{
    Button::Button() = default;

    Button::Button(const glm::vec2& position, const glm::vec2& size, const std::string& label_text, const std::shared_ptr<Font>& font, const glm::vec4& label_color, const std::shared_ptr<Texture> background_texture, const glm::vec4& background_color)
    : Widget(position, size),
      background(glm::mat3(1.0f), size, background_color, background_texture),
      label(glm::mat3(1.0f), label_text, font, label_color),
      hit_area(glm::mat3(1.0f), size)
    {
        add_node(background);
        add_node(label);
        add_node(hit_area);
    }

    void Button::set_label_text(const std::string& value) noexcept
    {
        label.set_text(value);
    }

    const std::string& Button::get_label_text() const noexcept
    {
        return label.get_text();
    }

    void Button::set_label_font(const std::shared_ptr<Font>& value) noexcept
    {
        label.set_font(value);
    }

    const std::shared_ptr<Font>& Button::get_label_font() const noexcept
    {
        return label.get_font();
    }

    void Button::set_label_color(const glm::vec4& value) noexcept
    {
        label.set_color(value);
    }

    const glm::vec4& Button::get_label_color() const noexcept
    {
        return label.get_color();
    }

    void Button::set_background_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        background.set_texture(value);
    }

    const std::shared_ptr<Texture>& Button::get_background_texture() const noexcept
    {
        return background.get_texture();
    }

    void Button::set_background_color(const glm::vec4& value) noexcept
    {
        background.set_color(value);
    }

    const glm::vec4& Button::get_background_color() const noexcept
    {
        return background.get_color();
    }

    rsig::connection Button::on_click(const std::function<void ()>& cb) noexcept
    {
        return hit_area.on_click(cb);
    }

    rsig::signal<>& Button::get_click_signal() noexcept
    {
        return hit_area.get_click_signal();
    }

    glm::vec2 Button::handle_size_request(const glm::vec2& value) noexcept
    {
        background.set_size(value);
        hit_area.set_size(value);
        return value;
    }
}
