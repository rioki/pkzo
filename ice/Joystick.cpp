// Ice Engine
// Copyright 2022 Sean Farrell
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
#include "Joystick.h"

namespace ice
{
    rsig::signal<uint8_t, float>& Joystick::get_axis_motion_signal() noexcept
    {
        return axis_motion_signal;
    }

    rsig::connection Joystick::on_axis_motion(const std::function<void(uint8_t, float)>& cb) noexcept
    {
        return axis_motion_signal.connect(cb);
    }

    rsig::signal<uint8_t, glm::ivec2>& Joystick::ball_motion_signa() noexcept
    {
        return ball_motion_signal;
    }

    rsig::connection Joystick::on_ball_motion(const std::function<void(uint8_t, glm::ivec2)>& cb) noexcept
    {
        return ball_motion_signal.connect(cb);
    }

    rsig::signal<uint8_t>& Joystick::get_button_down_signal() noexcept
    {
        return button_down_signal;
    }

    rsig::connection Joystick::on_button_down(const std::function<void(uint8_t)>& cb) noexcept
    {
        return button_down_signal.connect(cb);
    }

    rsig::signal<uint8_t>& Joystick::get_button_up_signal() noexcept
    {
        return button_up_signal;
    }

    rsig::connection Joystick::on_button_up(const std::function<void(uint8_t)>& cb) noexcept
    {
        return button_up_signal.connect(cb);
    }

    rsig::signal<uint8_t, glm::ivec2>& Joystick::get_hat_motion_signal() noexcept
    {
        return hat_motion_signal;
    }

    rsig::connection Joystick::on_hat_motion(const std::function<void(uint8_t, glm::ivec2)>& cb) noexcept
    {
        return hat_motion_signal.connect(cb);
    }
}
