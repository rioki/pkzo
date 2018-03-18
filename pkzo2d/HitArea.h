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

#ifndef _PKZO2D_HIT_AREA_H_
#define _PKZO2D_HIT_AREA_H_

#include "Widget.h"

#include <functional>

namespace pkzo
{
    class PKZO_EXPORT HitArea : public Widget
    {
    public:
        
        HitArea();

        ~HitArea();

        void on_enter(std::function<void ()> cb);

        void on_leave(std::function<void ()> cb);

        void on_click(std::function<void ()> cb);

        void handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov) override;

        void handle_mouse_press(unsigned int button, rgm::ivec2 pos) override;

        void handle_mouse_release(unsigned int button, rgm::ivec2 pos) override;

    private:
        std::function<void ()> enter_cb;
        std::function<void ()> leave_cb;
        std::function<void ()> click_cb;

        bool inside;
        bool click_inside;
    };
}

#endif
