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
#include "Text.h"

#include "ScreenRenderer.h"

namespace pkzo2d
{
    Text::Text() noexcept = default;

    Text::Text(const std::shared_ptr<Font>& f, const std::string& t) noexcept
    : font(f), text(t) {}

    Text::Text(const std::shared_ptr<Font>& f, const glm::vec4& c, const std::string& t) noexcept
    : font(f), color(c), text(t) {}

    Text::~Text() = default;

    void Text::set_position(const glm::vec2& value) noexcept
    {
        position = value;
    }

    const glm::vec2& Text::get_position() const noexcept
    {
        return position;
    }

    void Text::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        font = value;
        texture = nullptr;
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

    void Text::set_text(const std::string& value) noexcept
    {
        text = value;
        texture = nullptr;
    }

    const std::string& Text::get_text() const noexcept
    {
        return text;
    }

    glm::vec2 Text::get_size() const noexcept
    {
        if (texture)
        {
            return texture->get_size();
        }
        else if (font)
        {
            return font->estimate(text);
        }
        else
        {
            return {0.0f, 0.0f};
        }
    }

    void Text::render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept
    {
        if (font)
        {
            if (texture == nullptr)
            {
                texture = font->render(text);
            }

            renderer.draw_rectangle(offset + position, texture->get_size(), color, texture);
        }
    }
}
