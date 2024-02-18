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
#include "Text.h"

namespace pkzo
{
    Text::Text() noexcept = default;

    Text::Text(const std::u8string& text, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept
    : text(text), font(font), color(color)
    {
        check(font);
    }

    Text::Text(const glm::mat3& transform, const std::u8string& text, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept
    : ScreenNode(transform), text(text), font(font), color(color)
    {
        check(font);
    }

    void Text::set_text(const std::u8string& value) noexcept
    {
        text = value;
        text_image = nullptr;
    }

    const std::u8string& Text::get_text() const noexcept
    {
        return text;
    }

    void Text::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        check(value);
        font = value;
        text_image = nullptr;
    }

    const std::shared_ptr<Font>& Text::get_font() const noexcept
    {
        return font;
    }

    void Text::set_color(const glm::vec4& value) noexcept
    {
        color = value;
    }

    const glm::vec4& Text::get_color() const noexcept
    {
        return color;
    }

    /*void Text::draw(ScreenRenderer& renderer) const
    {
        if (font == nullptr)
        {
            return;
        }

        if (text_image == nullptr)
        {
            text_image = std::make_unique<Image>(font->render(text));
        }

        renderer.draw_rectangle(get_transform(), glm::vec2(text_image->get_size()), color, *text_image);
    }*/

}
