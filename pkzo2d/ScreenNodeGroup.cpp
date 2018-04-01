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

#include "ScreenNodeGroup.h"

namespace pkzo
{
    ScreenNodeGroup::ScreenNodeGroup() {}

    ScreenNodeGroup::~ScreenNodeGroup() {}

    void ScreenNodeGroup::add_widget(ScreenNode& widget) 
    {
        widgets.push_back(&widget);
    }

    void ScreenNodeGroup::remove_widget(ScreenNode& widget) 
    {
        auto i = std::find(widgets.begin(), widgets.end(), &widget);
        if (i != widgets.end())
        {
            widgets.erase(i);
        }
        else
        {
            throw std::logic_error("widget not in group");
        }
    }

    void ScreenNodeGroup::draw(Canvas& canvas, rgm::ivec2 offset) const 
    {
        for (const ScreenNode* widget : widgets)
        {
            widget->draw(canvas, position + offset);
        }
    }

    void ScreenNodeGroup::handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov) 
    {
        for (ScreenNode* widget : widgets)
        {
            widget->handle_mouse_move(pos - position, mov);
        }
    }

    void ScreenNodeGroup::handle_mouse_press(unsigned int button, rgm::ivec2 pos) 
    {
        for (ScreenNode* widget : widgets)
        {
            widget->handle_mouse_press(button, pos - position);
        }
    }

    void ScreenNodeGroup::handle_mouse_release(unsigned int button, rgm::ivec2 pos) 
    {
        for (ScreenNode* widget : widgets)
        {
            widget->handle_mouse_release(button, pos - position);
        }
    }    
}