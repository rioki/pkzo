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

#include "ScreenNode.h"

namespace pkzo
{
    ScreenNode::ScreenNode()
    : position(0, 0), size(15, 15) {}

    ScreenNode::~ScreenNode() {}

    void ScreenNode::set_position(const rgm::ivec2& value)
    {
        position = value;
    }

    const rgm::ivec2& ScreenNode::get_position() const
    {
        return position;
    }

    void ScreenNode::set_size(const rgm::ivec2& value)
    {
        size = value;
    }

    const rgm::ivec2& ScreenNode::get_size() const
    {
        return size;
    }

    void ScreenNode::draw(Canvas& canvas, rgm::ivec2 offset) const {}

    void ScreenNode::handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov) {}

    void ScreenNode::handle_mouse_press(unsigned int button, rgm::ivec2 pos) {}

    void ScreenNode::handle_mouse_release(unsigned int button, rgm::ivec2 pos) {}
}
