//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "HitArea.h"

namespace pkzo
{
    template <typename Enum>
    auto to_underlying(Enum value)
    {
        return static_cast<std::underlying_type<MouseButton>::type>(value);
    }

    HitArea::HitArea() noexcept = default;

    HitArea::HitArea(const glm::vec2& p, const glm::vec2& s) noexcept
    : position(p), size(s) {}

    HitArea::~HitArea() = default;

    void HitArea::set_position(const glm::vec2& value) noexcept
    {
        position = value;
    }

    const glm::vec2& HitArea::get_position() const noexcept
    {
        return position;
    }

    void HitArea::set_size(const glm::vec2& value) noexcept
    {
        size = value;
    }

    const glm::vec2& HitArea::get_size() const noexcept
    {
        return size;
    }

    void HitArea::on_enter(const std::function<void()>& cb) noexcept
    {
        enter_cb = cb;
    }

    void HitArea::on_leave(const std::function<void()>&cb) noexcept
    {
        leave_cb = cb;
    }

    void HitArea::on_mouse_move(const std::function<void(glm::vec2)>&cb) noexcept
    {
        mouse_move_cb = cb;
    }

    void HitArea::on_mouse_down(const std::function<void(MouseButton, glm::vec2)>&cb) noexcept
    {
        mouse_down_cb = cb;
    }

    void HitArea::on_mouse_up(const std::function<void(MouseButton, glm::vec2)>&cb) noexcept
    {
        mouse_up_cb = cb;
    }

    void HitArea::on_click(const std::function<void ()>& cb) noexcept
    {
        click_cb = cb;
    }

    void HitArea::handle_mouse_button_down(MouseButton button, glm::vec2 pos)
    {
        auto min = position - size / 2.0f;
        auto max = position + size / 2.0f;
        if (pos.x >= min.x && pos.y >= min.y &&
            pos.x <= max.x && pos.y <= max.y)
        {
            click_armed[to_underlying(button)] = true;
            if (mouse_down_cb)
            {
                auto local_pos = pos - position;
                mouse_down_cb(button, local_pos);
            }
        }
    }

    void HitArea::handle_mouse_button_up(MouseButton button, glm::vec2 pos)
    {
        if (click_armed[to_underlying(button)])
        {
            auto min = position - size / 2.0f;
            auto max = position + size / 2.0f;
            if (pos.x >= min.x && pos.y >= min.y &&
                pos.x <= max.x && pos.y <= max.y)
            {
                if (click_cb && button == MouseButton::LEFT)
                {
                    click_cb();
                }
            }

            if (mouse_up_cb)
            {
                auto local_pos = pos - position;
                mouse_up_cb(button, local_pos);
            }
        }
        click_armed[to_underlying(button)] = false;
    }

    void HitArea::handle_mouse_move(glm::vec2 pos, glm::vec2 rel)
    {
        auto min = position - size / 2.0f;
        auto max = position + size / 2.0f;
        if (pos.x >= min.x && pos.y >= min.y &&
            pos.x <= max.x && pos.y <= max.y)
        {
            if (mouse_in == false)
            {
                if (enter_cb)
                {
                    enter_cb();
                }
                mouse_in = true;
            }

            if (mouse_move_cb)
            {
                mouse_move_cb(pos);
            }
        }
        else
        {
            if (mouse_in == true)
            {
                if (leave_cb)
                {
                    leave_cb();
                }
                mouse_in = false;
            }
        }
    }
}

