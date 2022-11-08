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

#include "Style.h"

namespace ice::ui
{
    glm::vec2 safe_estimate(const std::shared_ptr<Font>& font, const std::string& text)
    {
        if (!font)
        {
            return glm::vec2(0.0f);
        }
        return glm::vec2(font->estimate(text));
    }

    Label::Label() noexcept = default;

    Label::Label(const std::shared_ptr<Style>& style, const std::string& caption)
    : Label(glm::vec2(0.0f), style, caption) {}

    Label::Label(const glm::vec2& position, const std::shared_ptr<Style>& style, const std::string& caption)
    : Label(position,
            caption,
            style->get_font("Button", "font"),
            style->get_color("Button", "color")) {}

    Label::Label(const std::string& caption, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept
    : Label(glm::vec2(0.0f), caption, font, color) {}

    Label::Label(const glm::vec2& position, const std::string& caption, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept
    : Widget(position, safe_estimate(font, caption)), label(glm::mat3(1.0f), caption, font, color)
    {
        add_node(label);
    }

    void Label::set_caption(const std::string& value) noexcept
    {
        label.set_text(value);
    }

    const std::string& Label::get_caption() const noexcept
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

    glm::vec2 Label::get_min_size() const noexcept
    {
        return label.get_size();
    }

    glm::vec2 Label::handle_size_request(const glm::vec2& value) noexcept
    {
        return glm::max(label.get_size(), value);
    }
}
