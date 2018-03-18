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

#include "HitArea.h"

namespace pkzo
{
    HitArea::HitArea()
    : inside(false), click_inside(false) {}

    HitArea::~HitArea() {}

    void HitArea::on_enter(std::function<void ()> cb)
    {
        enter_cb = cb;
    }

    void HitArea::on_leave(std::function<void ()> cb)
    {
        leave_cb = cb;
    }

    void HitArea::on_click(std::function<void ()> cb)
    {
        click_cb = cb;
    }

    void HitArea::handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov)     
    {
       rgm::ivec2 min = position;
       rgm::ivec2 max = position + size;

        if (pos[0] >= min[0] && pos[1] >= min[1] &&
            pos[0] <= max[0] && pos[1] <= max[1])
        {
            if (inside == false)
            {
                if (enter_cb) 
                {
                    enter_cb();
                }
                inside = true;
            }
        }
        else
        {
            if (inside == true)
            {
                if (leave_cb) 
                {
                    leave_cb();
                }
                inside = false;
            }
        }
    }

    void HitArea::handle_mouse_press(unsigned int button, rgm::ivec2 pos)
    {
       rgm::ivec2 min = position;
       rgm::ivec2 max = position + size;

        if (pos[0] >= min[0] && pos[1] >= min[1] &&
            pos[0] <= max[0] && pos[1] <= max[1])
        {
            click_inside = true;
        }
    }

    void HitArea::handle_mouse_release(unsigned int button, rgm::ivec2 pos)
    {
       rgm::ivec2 min = position;
       rgm::ivec2 max = position + size;

        if (pos[0] >= min[0] && pos[1] >= min[1] &&
            pos[0] <= max[0] && pos[1] <= max[1] && 
            click_inside)
        {
            if (click_cb) 
            {
                click_cb();
            }
        }

        click_inside = false;
    }
}
