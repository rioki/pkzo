// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Rectangle.h"

namespace pkzo
{
    Rectangle::Rectangle() noexcept = default;

    Rectangle::Rectangle(const glm::vec2& s) noexcept
    : size(s) {}

    Rectangle::Rectangle(const glm::vec2& s, const glm::vec4& c) noexcept
    : size(s), color(c) {}

    Rectangle::Rectangle(const glm::vec2& s, const std::shared_ptr<Image>& i) noexcept
    : size(s), image(i) {}

    Rectangle::Rectangle(const glm::vec2& s, const glm::vec4& c, const std::shared_ptr<Image>& i) noexcept
    : size(s), color(c), image(i) {}

    Rectangle::Rectangle(const glm::mat3& transform, const glm::vec2& size) noexcept
    : ScreenNode(transform), size(size) {}

    Rectangle::Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color) noexcept
    : ScreenNode(transform), size(size), color(color) {}

    Rectangle::Rectangle(const glm::mat3& transform, const glm::vec2& size, const std::shared_ptr<Image>& image) noexcept
    : ScreenNode(transform), size(size), image(image) {}

    Rectangle::Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Image>& image) noexcept
    : ScreenNode(transform), size(size), color(color), image(image) {}

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

    void Rectangle::set_image(const std::shared_ptr<Image>& value) noexcept
    {
        image = value;
    }

    const std::shared_ptr<Image>& Rectangle::get_image() const noexcept
    {
        return image;
    }

    void Rectangle::activate()
    {
        auto screen = get_root();
        check(screen);
        auto renderer = screen->get_renderer();
        check(renderer);
        if (image)
        {
            render_id = renderer->add_rectangle(get_transform(), size, color, *image);
        }
        else
        {
            render_id = renderer->add_rectangle(get_transform(), size, color);
        }
    }

    void Rectangle::deactivate()
    {
        auto screen = get_root();
        check(screen);
        auto renderer = screen->get_renderer();
        check(renderer);
        renderer->remove_rectangle(render_id);
    }
}
