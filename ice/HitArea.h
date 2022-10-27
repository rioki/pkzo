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

#pragma once
#include "config.h"

#include <rsig/rsig.h>

#include "ScreenNode.h"
#include "Mouse.h"

namespace ice
{
    class ICE_EXPORT HitArea : public ScreenNode
    {
    public:
        HitArea();
        HitArea(const glm::mat3& transform, const glm::vec2& size) noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        rsig::signal<bool, MouseButton, glm::vec2>& get_mouse_down_signal() noexcept;
        rsig::connection on_mouse_down(const std::function<void (bool, MouseButton, glm::vec2)>& cb) noexcept;

        rsig::signal<bool, MouseButton, glm::vec2>& get_mouse_up_signal() noexcept;
        rsig::connection on_mouse_up(const std::function<void (bool, MouseButton, glm::vec2)>& cb) noexcept;

        rsig::signal<>& get_click_signal() noexcept;
        rsig::connection on_click(const std::function<void ()>& cb) noexcept;

        rsig::signal<>& get_right_click_signal() noexcept;
        rsig::connection on_right_click(const std::function<void ()>& cb) noexcept;

        void activate() override;
        void deactivate() override;

        void handle_mouse_down(const MouseButton button, const glm::vec2& pos);
        void handle_mouse_up(const MouseButton button, const glm::vec2& pos);

    private:
        glm::vec2 size = {15.0f, 15.0f};
        rsig::signal<bool, MouseButton, glm::vec2> mouse_down_signal;
        rsig::signal<bool, MouseButton, glm::vec2> mouse_up_signal;
        rsig::signal<> click_signal;
        rsig::signal<> right_click_signal;

        bool left_inside  = false;
        bool right_inside = false;
    };
}
