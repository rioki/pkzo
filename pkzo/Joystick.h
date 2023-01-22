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

#pragma once
#include "config.h"

#include <functional>
#include <glm/fwd.hpp>
#include <rsig/rsig.h>

namespace pkzo
{
    class ICE_EXPORT Joystick
    {
    public:
        Joystick() noexcept = default;
        virtual ~Joystick() = default;

        virtual std::string get_name() const noexcept = 0;
        virtual uint8_t get_axis_count() const noexcept = 0;
        virtual uint8_t get_ball_count() const noexcept = 0;
        virtual uint8_t get_button_count() const noexcept = 0;
        virtual uint8_t get_hat_count() const noexcept = 0;

        rsig::signal<uint8_t, float>& get_axis_motion_signal() noexcept;
        rsig::connection on_axis_motion(const std::function<void (uint8_t, float)>& cb) noexcept;

        rsig::signal<uint8_t, glm::ivec2>& ball_motion_signa() noexcept;
        rsig::connection on_ball_motion(const std::function<void (uint8_t, glm::ivec2)>& cb) noexcept;

        rsig::signal<uint8_t>& get_button_down_signal() noexcept;
        rsig::connection on_button_down(const std::function<void (uint8_t)>& cb) noexcept;

        rsig::signal<uint8_t>& get_button_up_signal() noexcept;
        rsig::connection on_button_up(const std::function<void (uint8_t)>& cb) noexcept;

        rsig::signal<uint8_t, glm::ivec2>& get_hat_motion_signal() noexcept;
        rsig::connection on_hat_motion(const std::function<void (uint8_t, glm::ivec2)>& cb) noexcept;

    protected:
        rsig::signal<uint8_t, float>      axis_motion_signal;
        rsig::signal<uint8_t, glm::ivec2> ball_motion_signal;
        rsig::signal<uint8_t>             button_down_signal;
        rsig::signal<uint8_t>             button_up_signal;
        rsig::signal<uint8_t, glm::ivec2> hat_motion_signal;

    private:
        Joystick(const Joystick&) = delete;
        Joystick& operator = (const Joystick&) = delete;
    };
}
