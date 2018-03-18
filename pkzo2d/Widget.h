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

#ifndef _PKZO_WIDGET_H_
#define _PKZO_WIDGET_H_

#include <pkzo/defines.h>

#include <rgm/rgm.h>

namespace pkzo
{
        

    class Canvas;

    class PKZO_EXPORT Widget
    {
    public:

        Widget();

        Widget(const Widget&) = delete;

        virtual ~Widget();

        const Widget& operator = (const Widget&) = delete;

        void set_position(const rgm::ivec2& value);

        const rgm::ivec2& get_position() const;

        void set_size(const rgm::ivec2& value);

        const rgm::ivec2& get_size() const;

        virtual void draw(Canvas& canvas, rgm::ivec2 offset) const;

        virtual void handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov);

        virtual void handle_mouse_press(unsigned int button, rgm::ivec2 pos);

        virtual void handle_mouse_release(unsigned int button, rgm::ivec2 pos);

    protected:
       rgm::ivec2 position;
       rgm::ivec2 size;
    };
}

#endif
