// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "Text.h"

#include <algorithm>

#include <pkzo/Font.h>
#include <pkzo/Texture.h>

#include "Canvas.h"

namespace pkzo
{
    std::vector<std::string> explode(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> gibs;
        size_t start = 0;
        size_t end = 0;

        while ((start != std::string::npos) && (start < str.size()))
        {
            end = str.find(delimiter, start);

            std::string gib;
            if (end == std::string::npos)
            {
                gib = str.substr(start);
                start = std::string::npos;
            }
            else
            {
                gib = str.substr(start, end - start);
                start = end + delimiter.size();
            }
            gibs.push_back(gib);
        }

        return gibs;
    }

    Text::Text()
    : dirty(true) {}

    Text::Text(rgm::ivec2 p, std::shared_ptr<Font> f, const std::string& t, const rgm::vec4& c)
    : dirty(true), font(f), text(t), color(c)
    {
        position = p;
        if (font)
        {
            size = font->estimate(text);
        }
    }

    Text::~Text() {}

    void Text::set_font(std::shared_ptr<Font> value)
    {
        font  = value;
        dirty = true;

        if (font)
        {
            estimate();
        }
    }

    std::shared_ptr<Font> Text::get_font() const
    {
        return font;
    }

    void Text::set_text(const std::string& value)
    {
        text  = value;
        dirty = true;

        if (font)
        {
            estimate();
        }
    }

    const std::string& Text::get_text() const
    {
        return text;
    }

    void Text::set_color(const rgm::vec4& value)
    {
        color = value;
    }

    const rgm::vec4& Text::get_color() const
    {
        return color;
    }

    void Text::draw(Canvas& canvas, rgm::ivec2 offset) const
    {
        if (dirty)
        {
            auto lines = explode(text, "\n");
            textures.resize(lines.size());
            for (unsigned int i = 0; i < lines.size(); i++)
            {
                textures[i] = font->render(lines[i]);
            }
            dirty = false;
        }
        
        // TODO aligment
       rgm::ivec2 p2 = position + offset;
        for (auto& texture : textures)
        {
            canvas.draw_rectangle(p2, texture.get_size(), color, texture);
            p2[1] += texture.get_height();
        }
    }

    void Text::estimate()
    {
        auto lines = explode(text, "\n");
       rgm::ivec2 result(0, 0);
        for (auto& line : lines)
        {
            rgm::ivec2 es = font->estimate(line);
            result[0] = std::max<float>(result[0], es[0]);

            result[1] += es[1];
        }

        size = result;        
    }
}
