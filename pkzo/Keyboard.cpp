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

#include "Keyboard.h"

#include <array>

#include "stdex.h"
#include "EventRouter.h"

namespace pkzo
{
    Keyboard::Keyboard(EventRouter& event_router)
    : event_router(event_router)
    {
        event_con = event_router.on_event(rsig::mem_fun(this, &Keyboard::handle_events));
    }

    Keyboard::~Keyboard()
    {
        event_router.disconnect_event(event_con);
    }

    bool Keyboard::is_pressed(Key key) const
    {
        auto numkeys = 0;
        auto keys = SDL_GetKeyboardState(&numkeys);
        return keys[static_cast<size_t>(key)] == SDL_TRUE;
    }

    rsig::connection Keyboard::on_key_press(const std::function<void (KeyMod, Key)>& cb)
    {
        return key_press_signal.connect(cb);
    }

    void Keyboard::disconnect_key_press(const rsig::connection& con)
    {
        return key_press_signal.disconnect(con);
    }

    rsig::connection Keyboard::on_key_release(const std::function<void (KeyMod, Key)>& cb)
    {
        return key_release_signal.connect(cb);
    }

    void Keyboard::disconnect_key_release(const rsig::connection& con)
    {
        return key_release_signal.disconnect(con);
    }

    KeyMod to_keymod(Uint16 sdl_mod) noexcept
    {
        static const auto mods = std::array<KeyMod, 4>{KeyMod::SHIFT, KeyMod::CTRL, KeyMod::ALT, KeyMod::GUI};

        auto result = KeyMod::NONE;
        for (auto mod : mods)
        {
            if ((static_cast<Uint16>(mod) & sdl_mod) != KMOD_NONE)
            {
                result = result | mod;
            }
        }
        return result;
    }

    Key to_key(SDL_Scancode sdl_scancode) noexcept
    {
        return static_cast<Key>(sdl_scancode);
    }

    void Keyboard::handle_events(const SDL_Event& ev)
    {
        switch (ev.type)
        {
            case SDL_KEYDOWN:
                key_press_signal.emit(to_keymod(ev.key.keysym.mod), to_key(ev.key.keysym.scancode));
                break;
            case SDL_KEYUP:
                key_release_signal.emit(to_keymod(ev.key.keysym.mod), to_key(ev.key.keysym.scancode));
                break;
        }
    }
}
