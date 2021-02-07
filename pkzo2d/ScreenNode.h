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

#ifndef _PKZO2D_SCREEN_NODE_H_
#define _PKZO2D_SCREEN_NODE_H_

#include "config.h"

namespace pkzo2d
{
    using namespace pkzo;

    class ScreenRenderer;

    class PKZO2D_EXPORT ScreenNode
    {
    public:
        ScreenNode() noexcept;
        ScreenNode(const ScreenNode&) = delete;
        virtual ~ScreenNode();
        ScreenNode& operator = (const ScreenNode&) = delete;

        ScreenNode* get_parent() noexcept;
        const ScreenNode* get_parent() const noexcept;

        virtual void handle_mouse_button_down(MouseButton button, glm::vec2 position);
        virtual void handle_mouse_button_up(MouseButton button, glm::vec2 position);
        virtual void handle_mouse_move(glm::vec2 pos, glm::vec2 rel);

    protected:
        virtual void render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept;

    private:
        ScreenNode* parent = nullptr;

    friend class ScreenNodeGroup;
    };
}

#endif
