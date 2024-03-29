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

#pragma once

#include "ScreenNode.h"

#include "Image.h"
#include "InputHandler.h"

namespace pkzo
{
    class PKZO_EXPORT HitArea : public ScreenNode, public InputHandler
    {
    public:
        rex::signal<> on_click;

        HitArea() noexcept;
        explicit HitArea(const glm::vec2& size) noexcept;
        explicit HitArea(const glm::mat3& transform, const glm::vec2& size) noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void activate() override;
        void deactivate() override;

        void handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos) override;
        void handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos) override;

    private:
        glm::vec2 size = {15, 15};
        bool click_inside = false;
    };
}
