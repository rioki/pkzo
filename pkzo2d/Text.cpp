// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Text.h"

namespace pkzo2d
{
    Text::Text(Specs specs)
    : Shape({specs.parent, specs.transform}),
      color(specs.color),
      text(specs.text),
      font(specs.font),
      font_size(specs.font_size)
    {
        if (!font)
        {
            throw std::invalid_argument("Text: font is null");
        }
    }

    Text::~Text() = default;

    glm::vec2 Text::get_size() const
    {
        if (texture)
        {
            return glm::vec2(texture->get_size());
        }
        else
        {
            assert(font);
            return font->estimate(text, font_size);
        }
    }

    void Text::set_text(const std::u8string& value)
    {
        if (text != value)
        {
            text = value;
            texture.reset();
        }
    }

    const std::u8string& Text::get_text() const
    {
        return text;
    }

    void Text::set_color(const glm::vec4& value)
    {
        color = value;
    }

    void Text::set_font(const std::shared_ptr<Font>& value)
    {
        if (!value)
        {
            throw std::invalid_argument("Text::set_font: font is null");
        }
        if (font != value)
        {
            font = value;
            texture.reset();
        }
    }

    const std::shared_ptr<Font>& Text::get_font() const
    {
        return font;
    }

    void Text::set_font_size(unsigned int value)
    {
        if (font_size != value)
        {
            font_size = value;
            texture.reset();
        }
    }

    unsigned int Text::get_font_size() const
    {
        return font_size;
    }

    glm::mat4 Text::get_model_matrix() const
    {
        auto mm = Shape::get_model_matrix();
        return glm::scale(mm, glm::vec3(get_size(), 1.0f));
    }

    // defined in Rectangle.cpp
    std::shared_ptr<Mesh> create_unit_rectangle();

    std::shared_ptr<Mesh> Text::get_mesh() const
    {
        static auto cache = std::weak_ptr<Mesh>{};

        if (mesh)
        {
            return mesh;
        }

        mesh = cache.lock();
        if (mesh)
        {
            return mesh;
        }

        mesh = create_unit_rectangle();
        cache = mesh;
        return mesh;
    }

    glm::vec4 Text::get_color() const
    {
        return color;
    }

    std::shared_ptr<Texture> Text::get_texture() const
    {
        if (texture)
        {
            return texture;
        }

        assert(font);
        texture = font->render(text, font_size);
        return texture;
    }
}
