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

#ifndef _PKZO2D_HIT_AREA_H_
#define _PKZO2D_HIT_AREA_H_

#include "config.h"

#include <functional>

#include "ScreenNode.h"

namespace pkzo2d
{
    using namespace pkzo;

    class PKZO2D_EXPORT HitArea : public ScreenNode
    {
    public:
        HitArea() noexcept;
        HitArea(const glm::vec2& position, const glm::vec2& size) noexcept;
        ~HitArea();

        void set_position(const glm::vec2& value) noexcept;
        const glm::vec2& get_position() const noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void on_enter(const std::function<void ()>& cb) noexcept;
        void on_leave(const std::function<void ()>& cb) noexcept;
        void on_mouse_move(const std::function<void (glm::vec2)>& cb) noexcept;
        void on_mouse_down(const std::function<void (MouseButton, glm::vec2)>& cb) noexcept;
        void on_mouse_up(const std::function<void (MouseButton, glm::vec2)>& cb) noexcept;
        void on_click(const std::function<void ()>& cb) noexcept;

        void handle_mouse_button_down(MouseButton button, glm::vec2 position) override;
        void handle_mouse_button_up(MouseButton button, glm::vec2 position) override;
        void handle_mouse_move(glm::vec2 pos, glm::vec2 rel) override;

    private:
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 size     = glm::vec2(15.0f);

        std::function<void ()> enter_cb;
        std::function<void ()> leave_cb;
        std::function<void (glm::vec2)> mouse_move_cb;
        std::function<void (MouseButton, glm::vec2)> mouse_down_cb;
        std::function<void (MouseButton, glm::vec2)> mouse_up_cb;
        std::function<void ()> click_cb;

        bool click_armed[5] = {false};
        bool mouse_in = false;
    };
}

#endif
