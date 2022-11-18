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

using namespace std::string_view_literals;

namespace ice::ui
{
    glm::vec2 safe_estimate(in<std::shared_ptr<Font>> font, in<std::string> text)
    {
        if (!font)
        {
            return glm::vec2(0.0f);
        }
        return glm::vec2(font->estimate(text));
    }

    constexpr std::string_view get_style_id(in<TextStyle> variant)
    {
        switch (variant)
        {
            using enum ice::ui::TextStyle;
            case DEFAULT:
                return "Label"sv;
            case TITLE:
                return "Label/Title"sv;
            case SUBTITLE:
                return "Label/Subtitle"sv;
            case HEADING1:
                return "Label/Heading1"sv;
            case HEADING2:
                return "Label/Heading2"sv;
            case HEADING3:
                return "Label/Heading3"sv;
            case HEADING4:
                return "Label/Heading4"sv;
            case HEADING5:
                return "Label/Heading5"sv;
            case BOLD:
                return "Label/Bold"sv;
            case ITALLIC:
                return "Label/Itallic"sv;
            case BOLD_ITALIC:
                return "Label/BoldItallic"sv;
            case CODE:
                return "Label/Code"sv;
            default:
                std::terminate();
        }
    }

    Label::Label() noexcept = default;

    Label::Label(in<std::shared_ptr<Style>> style, in<std::string> caption)
    : Label(style, TextStyle::DEFAULT, caption) {}

    Label::Label(in<std::shared_ptr<Style>> style, in<TextStyle> variant, in<std::string> caption)
    : Label(glm::vec2(0.0f), style, variant, caption) {}

    Label::Label(in<glm::vec2> position, in<std::shared_ptr<Style>> style, in<std::string> caption)
    : Label(position, style, TextStyle::DEFAULT, caption) {}

    Label::Label(in<glm::vec2> _position, in<std::shared_ptr<Style>> _style, in<TextStyle> _variant, in<std::string> _caption)
    : Label(_position,
            _caption,
            _style->get_font(get_style_id(_variant), "font"),
            _style->get_color(get_style_id(_variant), "color"))
    {
        style = _style;
    }

    Label::Label(in<std::string> caption, in<std::shared_ptr<Font>> font, in<glm::vec4> color) noexcept
    : Label(glm::vec2(0.0f), caption, font, color) {}

    Label::Label(in<glm::vec2> position, in<std::string> caption, in<std::shared_ptr<Font>> font, in<glm::vec4> color) noexcept
    : Widget(position, safe_estimate(font, caption)), label(glm::mat3(1.0f), caption, font, color)
    {
        add_node(label);
    }

    void Label::set_caption(in<std::string> value) noexcept
    {
        label.set_text(value);
    }

    cref_t<std::string> Label::get_caption() const noexcept
    {
        return label.get_text();
    }

    void Label::set_font(in<std::shared_ptr<Font>> value) noexcept
    {
        label.set_font(value);
    }

    cref_t<std::shared_ptr<Font>> Label::get_font() const noexcept
    {
        return label.get_font();
    }

    void Label::set_color(in<glm::vec4> value) noexcept
    {
        label.set_color(value);
    }

    cref_t<glm::vec4> Label::get_color() const noexcept
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
