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

#pragma once

#include "Screen.h"

#include <rsig/rsig.h>

namespace pkzo
{
    class Scene;

    class PKZO_EXPORT HitArea : public ScreenNode
    {
    public:
        struct Init
        {
            Node*                    parent    = nullptr;
            glm::mat3                transform = glm::mat3(1.0f);
            glm::vec2                size      = glm::vec2(15.0f);
            std::function<void ()>   action;
        };

        HitArea(Init init);

        ~HitArea();

        void set_size(const glm::vec2& value);
        const glm::vec2& get_size() const;

        rsig::connection on_click(const std::function<void ()>& handler);

        //void handle_mouse_button_down(glm::vec2 pos, MouseButton button) override;

    private:
        glm::vec2      size;
        rsig::signal<> click_signal;
    };
}
