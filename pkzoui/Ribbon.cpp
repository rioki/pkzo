/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Ribbon.h"

#include <algorithm>
#include <pkzo/pkzo.h>

namespace pkzo
{

    Ribbon::Ribbon() 
    {
        add_widget(background);
    }

    Ribbon::~Ribbon() {}

    void Ribbon::set_width(int value)
    {
        size[0] = value;
        background.set_size(size);
    }

    void Ribbon::set_font(std::shared_ptr<Font> value)
    {
        font = value;
    }

    std::shared_ptr<Font> Ribbon::get_font() const
    {
        return font;
    }

    void Ribbon::set_text_color(const vec4& value)
    {
        text_color = value;
    }

    const vec4& Ribbon::get_text_color()
    {
        return text_color;
    }

    void Ribbon::set_background_color(const vec4& value)
    {
        background.set_color(value);
    }

    const vec4& Ribbon::get_background_color() const
    {
        return background.get_color();
    }

    void Ribbon::add_icon(std::shared_ptr<Texture> icon, const std::string& caption, std::function<void ()> cb)
    {
        std::unique_ptr<Element> elem(new Element);
        elem->set_icon(icon);
        elem->set_caption(caption);
        elem->set_font(font);
        elem->set_text_color(text_color);
        elem->on_click(cb);

        size[1] = std::max(size[1], elem->get_size()[1]);
        background.set_size(size);

        if (!elements.empty())
        {
            ivec2 pp = elements.back()->get_position();
            ivec2 sp = elements.back()->get_size();

            elem->set_position(ivec2(pp[0] + sp[0], 0));
        }

        add_widget(*elem);
        elements.push_back(std::move(elem));
    }

    Ribbon::Element::Element()
    {
        add_widget(icon);
        add_widget(caption);
        add_widget(hitarea);
    }

    void Ribbon::Element::set_icon(std::shared_ptr<Texture> value)
    {
        icon.set_texture(value);
        icon.set_size(value->get_size());
        layout();
    }

    std::shared_ptr<Texture> Ribbon::Element::get_icon() const
    {
        return icon.get_texture();
    }
    
    void Ribbon::Element::set_caption(const std::string& value)
    {
        caption.set_text(value);
        layout();
    }

    const std::string& Ribbon::Element::get_caption() const
    {
        return caption.get_text();
    }

    void Ribbon::Element::set_font(std::shared_ptr<Font> value)
    {
        caption.set_font(value);
        layout();
    }

    std::shared_ptr<Font> Ribbon::Element::get_font() const
    {
        return caption.get_font();
    }

    void Ribbon::Element::set_text_color(const vec4& value)
    {
        icon.set_color(value);
        caption.set_color(value);
        layout();
    }

    const vec4& Ribbon::Element::get_text_color()
    {
        return caption.get_color();
    }

    void Ribbon::Element::on_click(std::function<void ()> cb)
    {
        hitarea.on_click(cb);
    }

    void Ribbon::Element::layout()
    {
        ivec2 is = icon.get_size();
        ivec2 cs = caption.get_size();

        size[0] = std::max(is[0], cs[0]) + 20;
        size[1] = is[1] + cs[1] + 15;

        icon.set_position(ivec2((size[0] - is[0]) / 2 + 10, 5));
        caption.set_position(ivec2((size[0] - cs[0]) / 2 + 10, is[1] + 10));

        hitarea.set_size(size);
    }
}
