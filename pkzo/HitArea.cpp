// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "HitArea.h"

namespace pkzo
{
    HitArea::HitArea() = default;

    HitArea::HitArea(const glm::vec2& _size) noexcept
    : size(_size) {}

    HitArea::HitArea(const glm::mat3& transform, const glm::vec2& _size) noexcept
    : ScreenNode(transform), size(_size) {}

    void HitArea::set_size(const glm::vec2& value) noexcept
    {
        size = value;
    }

    const glm::vec2& HitArea::get_size() const noexcept
    {
        return size;
    }

    rsig::signal<bool, MouseButton, glm::vec2>& HitArea::get_mouse_down_signal() noexcept
    {
        return mouse_down_signal;
    }

    rsig::connection HitArea::on_mouse_down(const std::function<void(bool, MouseButton, glm::vec2)>& cb) noexcept
    {
        return mouse_down_signal.connect(cb);
    }

    rsig::signal<bool, MouseButton, glm::vec2>& HitArea::get_mouse_up_signal() noexcept
    {
        return mouse_up_signal;
    }

    rsig::connection HitArea::on_mouse_up(const std::function<void(bool, MouseButton, glm::vec2)>& cb) noexcept
    {
        return mouse_up_signal.connect(cb);
    }

    rsig::signal<>& HitArea::get_click_signal() noexcept
    {
        return click_signal;
    }

    rsig::connection HitArea::on_click(const std::function<void()>& cb) noexcept
    {
        return click_signal.connect(cb);
    }

    rsig::signal<>& HitArea::get_right_click_signal() noexcept
    {
        return right_click_signal;
    }

    rsig::connection HitArea::on_right_click(const std::function<void()>& cb) noexcept
    {
        return right_click_signal.connect(cb);
    }

    void HitArea::activate()
    {
        ScreenNode::activate();

        auto screen = get_root();
        assert(screen != nullptr);
        screen->add_hitarea(this);
    }

    void HitArea::deactivate()
    {
        auto screen = get_root();
        assert(screen != nullptr);
        screen->remove_hitarea(this);

        ScreenNode::deactivate();
    }

bool is_inside_rect(const glm::mat3& tra, const glm::vec2& size, const glm::vec2& m)
    {
        auto hs = size / 2.0f;
        auto a  = glm::transform(tra, glm::vec2(-hs.x, -hs.y));
        auto b  = glm::transform(tra, glm::vec2(-hs.x,  hs.y));
        auto c  = glm::transform(tra, glm::vec2( hs.x, -hs.y));
        auto ab = b - a;
        auto ac = c - a;

        auto am = m - a;
        auto u = glm::dot(am, ab);
        auto v = glm::dot(am, ac);
        auto dab = glm::dot(ab, ab);
        auto dac = glm::dot(ac, ac);
        return u >= 0.0f && v >= 0.0f && u <= dab && v <= dac;
    }

    void HitArea::handle_mouse_down(const MouseButton button, const glm::vec2& pos)
    {
        auto wt = get_world_transform();
        auto wp = glm::transform(inverse(wt), pos);
        auto inside = is_inside_rect(wt, size, pos);
        mouse_down_signal.emit(inside, button, wp);

        switch (button)
        {
            case MouseButton::LEFT:
                left_inside = inside;
                break;
            case MouseButton::RIGHT:
                right_inside = inside;
                break;
            default:
                // don't care
                break;
        }
    }

    void HitArea::handle_mouse_up(const MouseButton button, const glm::vec2& pos)
    {
        auto wt = get_world_transform();
        auto wp = glm::transform(inverse(wt), pos);
        auto inside = is_inside_rect(wt, size, pos);
        mouse_up_signal.emit(inside, button, wp);

        switch (button)
        {
        case MouseButton::LEFT:
            if (inside && left_inside)
            {
                click_signal.emit();
            }
            left_inside = false; // reset in all cases
            break;
        case MouseButton::RIGHT:
            if (inside && right_inside)
            {
                right_click_signal.emit();
            }
            right_inside = false;
            break;
        default:
            // don't care
            break;
        }
    }
}
