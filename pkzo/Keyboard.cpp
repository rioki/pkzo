// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "Keyboard.h"

#include "debug.h"
#include "EventRouter.h"

namespace pkzo
{
    Keyboard::Keyboard(EventRouter& _router)
    : router(_router)
    {
        router_connection = router.get_event_signal().connect(rsig::mem_fun(this, &Keyboard::handle_events));
    }

    Keyboard::~Keyboard()
    {
        router.get_event_signal().disconnect(router_connection);
    }

    bool Keyboard::is_pressed(Key key) const noexcept
    {
        int numkeys = 0;
        auto keys = SDL_GetKeyboardState(&numkeys);
        check(keys != nullptr);
        check(numkeys < static_cast<int>(key));
        return keys[static_cast<int>(key)] == SDL_TRUE;
    }

    rsig::signal<KeyMod, Key>& Keyboard::get_key_press_signal() noexcept
    {
        return key_press_signal;
    }

    rsig::signal<KeyMod, Key>& Keyboard::get_key_release_signal() noexcept
    {
        return key_release_signal;
    }

    rsig::signal<std::string>& Keyboard::get_text_signal() noexcept
    {
        return text_signal;
    }

    void Keyboard::handle_events(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            key_press_signal.emit(static_cast<KeyMod>(event.key.keysym.mod), static_cast<Key>(event.key.keysym.scancode));
            break;
        case SDL_KEYUP:
            key_release_signal.emit(static_cast<KeyMod>(event.key.keysym.mod), static_cast<Key>(event.key.keysym.scancode));
            break;
        case SDL_TEXTINPUT:
            text_signal.emit(event.text.text);
            break;
        default:
            // don't care
            break;
        }
    }
}
