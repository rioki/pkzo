// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "pch.h"
#include "HitArea.h"

namespace pkzo
{
    HitArea::HitArea() noexcept = default;

    HitArea::HitArea(const glm::vec2& s) noexcept
    : size(s) {}

    HitArea::HitArea(const glm::mat3& t, const glm::vec2& s) noexcept
    : ScreenNode(t), size(s) {}

    void HitArea::set_size(const glm::vec2& value) noexcept
    {
        size = value;
    }

    const glm::vec2& HitArea::get_size() const noexcept
    {
        return size;
    }

    void HitArea::activate()
    {
        ScreenNode::activate();

        auto screen = get_root();
        check(screen);
        screen->add_input_handler(this);
    }

    void HitArea::deactivate()
    {
        auto screen = get_root();
        check(screen);
        screen->remove_input_handler(this);

        ScreenNode::deactivate();
    }

    void HitArea::handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos)
    {
        auto position = glm::inverse(get_world_transform()) * glm::vec3(pos, 1.0f);
        if (position.x >= 0 && position.x <= size.x && position.y >= 0 && position.y <= size.y)
        {
            click_inside = true;
        }
        else
        {
            click_inside = false;
        }
    }

    void HitArea::handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos)
    {
        if (click_inside)
        {
            auto position = glm::inverse(get_world_transform()) * glm::vec3(pos, 1.0f);
            if (position.x >= 0 && position.x <= size.x && position.y >= 0 && position.y <= size.y)
            {
                on_click();
            }
        }
    }
}
