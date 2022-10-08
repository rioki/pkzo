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

#include "Texture.h"

namespace ice
{
    Text::Text(const glm::mat3& tr, const std::string& te, const std::shared_ptr<Font>& f) noexcept
    : Text(tr, te, f, glm::vec4(1.0f)) {}

    Text::Text(const glm::mat3& transform, const std::string& t, const std::shared_ptr<Font>& f, const glm::vec4& c) noexcept
    : Rectangle(transform), text(t), font(f), color(c)
    {
        assert(font);
        texture = font->render(text);
        set_size(glm::vec2(texture->get_size()));
        set_color(color);
        set_texture(texture);
    }

    void Text::set_text(const std::string& value) noexcept
    {
        text = value;

        assert(font);
        texture = font->render(text);
        set_size(glm::vec2(texture->get_size()));
        set_texture(texture);
    }

    const std::string& Text::get_text() const noexcept
    {
        return text;
    }

    void Text::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        font = value;

        assert(font);
        texture = font->render(text);
        set_size(glm::vec2(texture->get_size()));
        set_texture(texture);
    }

    const std::shared_ptr<Font>& Text::get_font() const noexcept
    {
        return font;
    }
}