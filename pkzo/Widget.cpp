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
#include "Widget.h"

namespace pkzo
{
    Widget::Widget() noexcept = default;

    Widget::Widget(const glm::vec2& _size) noexcept
    : size(_size) {}

    Widget::Widget(const glm::vec2& _position, const glm::vec2& _size) noexcept
    : ScreenNodeGroup(glm::translate(_position)), size(_size) {}

    void Widget::set_position(const glm::vec2& value) noexcept
    {
        set_transform(glm::translate(value));
    }

    glm::vec2 Widget::get_position() const noexcept
    {
        return glm::transform(get_transform(), glm::vec2(0.0f));
    }

    void Widget::set_size(const glm::vec2& value) noexcept
    {
        size = handle_size_request(value);
    }

    const glm::vec2& Widget::get_size() const noexcept
    {
        return size;
    }

    glm::vec2 Widget::get_min_size() const noexcept
    {
        return glm::vec2(1.0f);
    }

    glm::vec2 Widget::handle_size_request(const glm::vec2& value) noexcept
    {
        // by default just accept the given value
        return value;
    }
}
