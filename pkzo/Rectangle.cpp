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

#include "ScreenRenderer.h"

namespace pkzo
{
    Rectangle::Rectangle() noexcept = default;

    Rectangle::Rectangle(const std::shared_ptr<Texture>& t) noexcept
    : texture(t)
    {
        assert(texture);
        size = texture->get_size();
    }

    Rectangle::Rectangle(const std::shared_ptr<Texture>& t, const glm::vec2& s) noexcept
    : texture(t), size(s) {}

    Rectangle::Rectangle(const glm::vec4& c, const glm::vec2& s) noexcept
    : color(c), size(s) {}

    Rectangle::Rectangle(const std::shared_ptr<Texture>& t, const glm::vec4& c) noexcept
    : texture(t), color(c)
    {
        assert(texture);
        size = texture->get_size();
    }

    Rectangle::Rectangle(const std::shared_ptr<Texture>& t, const glm::vec4& c, const glm::vec2& s) noexcept
    : texture(t), color(c), size(s) {}

    Rectangle::~Rectangle() = default;

    void Rectangle::set_position(const glm::vec2& value) noexcept
    {
        position = value;
    }

    const glm::vec2& Rectangle::get_position() const noexcept
    {
        return position;
    }

    void Rectangle::set_size(const glm::vec2& value) noexcept
    {
        size = value;
    }

    const glm::vec2& Rectangle::get_size() const noexcept
    {
        return size;
    }

    void Rectangle::set_color(const glm::vec4& value) noexcept
    {
        color = value;
    }

    const glm::vec4& Rectangle::get_color() const noexcept
    {
        return color;
    }

    void Rectangle::set_texture(const std::shared_ptr<Texture>& value)
    {
        texture = value;
    }

    const std::shared_ptr<Texture>& Rectangle::get_texture() const
    {
        return texture;
    }

    void Rectangle::render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept
    {
        renderer.draw_rectangle(offset + position, size, color, texture);
    }
}
