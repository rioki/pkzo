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

#include "pch.h"
#include "Keyboard.h"

#include "EventRouter.h"

namespace pkzo
{
    Keyboard::Keyboard(EventRouter& er)
    : event_router(er)
    {
        event_router.add_handler(this);
    }

    Keyboard::~Keyboard()
    {
        event_router.remove_handler(this);
    }

    bool Keyboard::is_pressed(Key key) const noexcept
    {
        int numkeys = 0;
        auto keys = SDL_GetKeyboardState(&numkeys);
        check(keys != nullptr);
        check(numkeys < static_cast<int>(key));
        return keys[static_cast<int>(key)] == SDL_TRUE;
    }

    rex::connection Keyboard::on_key_press(const std::function<void (KeyMod, Key)>& cb) noexcept
    {
        return key_press_signal.connect(cb);
    }

    rex::signal<KeyMod, Key>& Keyboard::get_key_press_signal() noexcept
    {
        return key_press_signal;
    }

    rex::connection Keyboard::on_key_release(const std::function<void (KeyMod, Key)>& cb) noexcept
    {
        return key_release_signal.connect(cb);
    }

    rex::signal<KeyMod, Key>& Keyboard::get_key_release_signal() noexcept
    {
        return key_release_signal;
    }

    rex::connection Keyboard::on_text(const std::function<void (const std::string_view)>& cb) noexcept
    {
        return text_signal.connect(cb);
    }

    rex::signal<const std::string_view>& Keyboard::get_text_signal() noexcept
    {
        return text_signal;
    }

    void Keyboard::handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key)
    {
        key_press_signal.emit(mod, key);
    }

    void Keyboard::handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key)
    {
        key_release_signal.emit(mod, key);
    }

    void Keyboard::handle_keboard_text(const std::string_view text)
    {
        text_signal.emit(text);
    }
}
