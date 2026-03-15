// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Screen.h"

#include "Renderer.h"

namespace pkzo
{
    Screen::Screen(Specs specs)
    : size(specs.size) {}

    Screen::~Screen()
    {
        // delete all children, before removing services
        remove_all_children();
    }

    Renderer* Screen::get_renderer()
    {
        if (!renderer)
        {
            renderer = std::make_unique<Renderer>(size);
        }
        return renderer.get();
    }

    void Screen::set_size(const glm::vec2& value)
    {
        size = value;
        if (renderer)
        {
            renderer->resize(value);
        }
    }

    const glm::vec2& Screen::get_size() const
    {
        return size;
    }

    void Screen::draw(pkzo::GraphicContext& gc)
    {
        if (renderer)
        {
            renderer->render(gc);
        }
    }
}
