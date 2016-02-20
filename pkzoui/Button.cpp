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

#include "Button.h"

namespace pkzo
{
    Button::Button() 
    {
        // TODO usefull default values
        add_widget(background);
        add_widget(label);
        add_widget(hitarea);
    }

    Button::~Button() {}

    void Button::set_label(const std::string& value)
    {
        label.set_text(value);
    }

    const std::string& Button::get_label() const
    {
        return label.get_text();
    }

    void Button::set_label_color(const vec4& value)
    {
        label.set_color(value);
    }

    const vec4& Button::get_label_color() const
    {
        return label.get_color();
    }

    void Button::set_label_font(std::shared_ptr<Font> value)
    {
        label.set_font(value);
    }

    std::shared_ptr<Font> Button::get_label_font() const
    {
        return label.get_font();
    }

    void Button::set_background_color(const vec4& value)
    {
        background.set_color(value);
    }

    const vec4& Button::get_background_color() const
    {
        return background.get_color();
    }

    void Button::set_background_texture(std::shared_ptr<Texture> value)
    {
        background.set_texture(value);
    }

    std::shared_ptr<Texture> Button::get_background_texture() const
    {
        return background.get_texture();
    }

    void Button::on_click(std::function<void ()> cb)
    {
        hitarea.on_click(cb);
    }

    void Button::draw(Canvas& canvas, ivec2 offset) const 
    {
        // TODO find a better place to do this
        ivec2 dx = get_size() - label.get_size();
        const_cast<Text&>(label).set_position(dx / 2);
        const_cast<HitArea&>(hitarea).set_size(size);

        WidgetGroup::draw(canvas, offset);
    }
}
