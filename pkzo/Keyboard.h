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

#include <functional>

#include <rex/signal.h>

#include "defines.h"
#include "InputHandler.h"

namespace pkzo
{
    class EventRouter;

    class PKZO_EXPORT Keyboard : public InputHandler
    {
    public:
        Keyboard(EventRouter& er);
        ~Keyboard();

        bool is_pressed(Key key) const noexcept;

        rex::connection on_key_press(const std::function<void (KeyMod, Key)>& cb) noexcept;
        rex::signal<KeyMod, Key>& get_key_press_signal() noexcept;

        rex::connection on_key_release(const std::function<void (KeyMod, Key)>& cb) noexcept;
        rex::signal<KeyMod, Key>& get_key_release_signal() noexcept;

        rex::connection on_text(const std::function<void (const std::string_view)>& cb) noexcept;
        rex::signal<const std::string_view>& get_text_signal() noexcept;

        void handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key) override;
        void handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key) override;
        void handle_keboard_text(const std::string_view text) override;

    private:
        EventRouter&             event_router;
        rex::signal<KeyMod, Key> key_press_signal;
        rex::signal<KeyMod, Key> key_release_signal;
        rex::signal<const std::string_view> text_signal;

        Keyboard(const Keyboard&) = delete;
        Keyboard& operator = (const Keyboard&) = delete;
    };
}
