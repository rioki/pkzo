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

#include "HitArea.h"

namespace pkzo2d
{
    HitArea::HitArea(Specs specs)
    : Node({specs.parent, specs.transform}),
      size(specs.size)
    {
        if (specs.action)
        {
            click_signal.connect(specs.action);
        }
    }

    HitArea::~HitArea() = default;

    void HitArea::set_size(const glm::vec2& value)
    {
        size = value;
    }

    const glm::vec2& HitArea::get_size() const
    {
        return size;
    }

    rsig::connection HitArea::on_click(const std::function<void ()>& handler)
    {
        return click_signal.connect(handler);
    }

    void HitArea::handle_mouse_button_down(glm::vec2 pos, MouseButton button)
    {
        if (button == MouseButton::LEFT)
        {
            auto gt        = get_global_transform();
            auto invgt     = glm::inverse(gt);
            auto local_pos = glm::vec2(invgt * glm::vec3(pos, 1.0f));

            auto hs = size * 0.5f;
            if (glm::all(glm::lessThanEqual(glm::abs(local_pos), hs)))
            {
                click_signal.emit();
            }
        }
    }
}
