// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "SdlKeyboard.h"

namespace ice
{
    bool SdlKeyboard::is_pressed(Key key) const noexcept
    {
        int numkeys = 0;
        auto keys = SDL_GetKeyboardState(&numkeys);
        assert(keys != nullptr);
        assert(numkeys < static_cast<int>(key));
        return keys[static_cast<int>(key)] == SDL_TRUE;
    }

    Key sdl2key(SDL_Scancode sc)
    {
        return static_cast<Key>(sc);
    }

    KeyMod sdl2mod(Uint16 mod)
    {
        auto result = KeyMod::NONE;

        if ((mod & KMOD_SHIFT) != 0)
        {
            result |= KeyMod::SHIFT;
        }
        if ((mod & KMOD_CTRL) != 0)
        {
            result |= KeyMod::CTRL;
        }
        if ((mod & KMOD_ALT) != 0)
        {
            result |= KeyMod::ALT;
        }
        if ((mod & KMOD_GUI) != 0)
        {
            result |= KeyMod::META;
        }

        return result;
    }

    void SdlKeyboard::handle_event(const SDL_Event& event) const
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            key_down_signal.emit(sdl2mod(event.key.keysym.mod), sdl2key(event.key.keysym.scancode));
            break;
        case SDL_KEYUP:
            key_up_signal.emit(sdl2mod(event.key.keysym.mod), sdl2key(event.key.keysym.scancode));
            break;
        case SDL_TEXTINPUT:
            text_signal.emit(event.text.text);
            break;
        default:
            assert(false);
            break;
        }
    }
}