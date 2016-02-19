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

#include "Widget.h"

namespace pkzo
{
    Widget::Widget()
    : position(0, 0), size(15, 15) {}

    Widget::~Widget() {}

    void Widget::set_position(const ivec2& value)
    {
        position = value;
    }

    const ivec2& Widget::get_position() const
    {
        return position;
    }

    void Widget::set_size(const ivec2& value)
    {
        size = value;
    }

    const ivec2& Widget::get_size() const
    {
        return size;
    }

    void Widget::draw(Canvas& canvas) const {}

    void Widget::handle_mouse_move(ivec2 pos, ivec2 mov) {}

    void Widget::handle_mouse_down(unsigned int button, ivec2 pos) {}

    void Widget::handle_mouse_up(unsigned int button, ivec2 pos) {}
}
