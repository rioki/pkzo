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
#include "Label.h"

namespace ice::ui
{
    Label::Label() noexcept = default;

    Label::Label(const glm::mat3& transform, const std::string& text, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept
    : ScreenNodeGroup(transform), label(glm::mat3(1.0f), text, font, color)
    {
        add_node(label);
    }

    const glm::vec2& Label::get_size() const noexcept
    {
        return label.get_size();
    }

    void Label::set_text(const std::string& value) noexcept
    {
        label.set_text(value);
    }

    const std::string& Label::get_text() const noexcept
    {
        return label.get_text();
    }

    void Label::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        label.set_font(value);
    }

    const std::shared_ptr<Font>& Label::get_font() const noexcept
    {
        return label.get_font();
    }

    void Label::set_color(const glm::vec4& value) noexcept
    {
        label.set_color(value);
    }

    const glm::vec4& Label::get_color() const noexcept
    {
        return label.get_color();
    }
}
