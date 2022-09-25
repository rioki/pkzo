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
#include "Mouse.h"

namespace ice
{
    rsig::signal<MouseButton, glm::ivec2>& Mouse::get_button_down_signal() noexcept
    {
        return button_down_signal;
    }

    rsig::connection Mouse::on_button_down(const std::function<void(MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_down_signal.connect(cb);
    }

    rsig::signal<MouseButton, glm::ivec2>& Mouse::get_button_up_signal() noexcept
    {
        return button_up_signal;
    }

    rsig::connection Mouse::on_button_up(const std::function<void(MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_up_signal.connect(cb);
    }

    rsig::signal<glm::ivec2, glm::ivec2>& Mouse::get_move_signal() noexcept
    {
        return move_signal;
    }

    rsig::connection Mouse::on_move(const std::function<void(glm::ivec2, glm::ivec2)>& cb) noexcept
    {
        return move_signal.connect(cb);
    }

    rsig::signal<glm::ivec2>& Mouse::get_wheel_signal() noexcept
    {
        return wheel_signal;
    }

    rsig::connection Mouse::on_wheel(const std::function<void(glm::ivec2)>& cb) noexcept
    {
        return wheel_signal.connect(cb);
    }
}
