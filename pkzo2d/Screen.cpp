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

#include "Screen.h"

#include <pkzo/Texture.h>

#include "Canvas.h"
#include "ScreenNode.h"

namespace pkzo
{
    Screen::Screen(const rgm::ivec2& s)
    : size(s), background_color(0x0000000) {}

    Screen::~Screen() {}

    void Screen::set_size(const rgm::ivec2& value)
    {
        size = value;
    }

    const rgm::ivec2& Screen::get_size() const
    {
        return size;
    }

    void Screen::set_background_color(const rgm::vec4& value)
    {
        background_color = value;
    }

    const rgm::vec4& Screen::get_background_color() const
    {
        return background_color;
    }

    void Screen::set_background_texture(std::shared_ptr<Texture> value)
    {
        background_texture = value;
    }

    std::shared_ptr<Texture> Screen::get_background_texture() const
    {
        return background_texture;
    }

    void Screen::add_node(std::shared_ptr<ScreenNode> node)
    {
        nodes.push_back(node);
    }

    void Screen::remove_node(std::shared_ptr<ScreenNode> node)
    {
        auto i = std::find(nodes.begin(), nodes.end(), node);
        if (i != nodes.end())
        {
            nodes.erase(i);
        }
        else
        {
            throw std::logic_error(__FUNCTION__": node not on screen");
        }
    }

    void Screen::draw(Canvas& canvas) const
    {
        canvas.set_size(size);

        if (background_texture)
        {
            canvas.draw_rectangle(rgm::ivec2(0, 0), size, background_color, *background_texture);
        }
        else
        {
            canvas.draw_rectangle(rgm::ivec2(0, 0), size, background_color);
        }

        for (auto node : nodes)
        {
            node->draw(canvas, rgm::ivec2(0, 0));
        }
    }

    void Screen::handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov)
    {
        for (auto node : nodes)
        {
            node->handle_mouse_move(pos, mov);
        }
    }
    
    void Screen::handle_mouse_press(unsigned int button, rgm::ivec2 pos)
    {
        for (auto node : nodes)
        {
            node->handle_mouse_press(button, pos);
        }
    }

    void Screen::handle_mouse_release(unsigned int button, rgm::ivec2 pos)
    {
        for (auto node : nodes)
        {
            node->handle_mouse_release(button, pos);
        }
    }
}
