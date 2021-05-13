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

#ifndef _ICE_KEYBOARD_H_
#define _ICE_KEYBOARD_H_

#include "config.h"

#include <functional>
#include <glm/fwd.hpp>

#include "enums.h"

union SDL_Event;

namespace pkzo
{
    class PKZO_EXPORT Keyboard
    {
    public:
        Keyboard() noexcept;
        Keyboard(const Keyboard&) = delete;
        ~Keyboard();
        Keyboard& operator = (const Keyboard&) = delete;

        bool is_pressed(Key key) const noexcept;

        void on_key_down(const std::function<void (KeyMod, Key)>& cb);
        void on_key_up(const std::function<void (KeyMod, Key)>& cb);
        void on_text(const std::function<void (const std::string_view)>& cb);

    private:
        std::function<void (KeyMod, Key)>            key_down_cb;
        std::function<void (KeyMod, Key)>            key_up_cb;
        std::function<void (const std::string_view)> text_cb;

        void handle_event(const SDL_Event& event) const;

    friend class Engine;
    };
}

#endif
