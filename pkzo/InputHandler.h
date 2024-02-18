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

#include <glm/glm.hpp>

#include "defines.h"
#include "Mouse.h"
#include "Keyboard.h"

namespace pkzo
{
    class PKZO_EXPORT InputHandler
    {
    public:
        virtual ~InputHandler() = default;

        virtual void handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos) = 0;
        virtual void handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos)  = 0;
        virtual void handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel)  = 0;
        virtual void handle_mouse_wheel(glm::ivec2 rel)  = 0;

        virtual void handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key) = 0;
        virtual void handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key) = 0;
        virtual void handle_keboard_text(const std::string_view text) = 0;
    };
}
