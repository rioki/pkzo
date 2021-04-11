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
#include "ScreenNode.h"

namespace pkzo::two
{
    ScreenNode::ScreenNode() noexcept = default;

    ScreenNode::~ScreenNode() = default;

    ScreenNode* ScreenNode::get_parent() noexcept
    {
        return parent;
    }

    const ScreenNode* ScreenNode::get_parent() const noexcept
    {
        return parent;
    }

    void ScreenNode::animate(std::chrono::milliseconds dt) {}

    void ScreenNode::handle_mouse_button_down(MouseButton button, glm::vec2 position) {}
    void ScreenNode::handle_mouse_button_up(MouseButton button, glm::vec2 position) {}
    void ScreenNode::handle_mouse_move(glm::vec2 pos, glm::vec2 rel) {}

    void ScreenNode::handle_key_down(KeyMod mod, Key key) {}
    void ScreenNode::handle_key_up(KeyMod mod, Key key) {}
    void ScreenNode::handle_text(const std::string_view text) {}

    void ScreenNode::render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept {}
}
