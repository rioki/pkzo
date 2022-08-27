// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Keyboard.h"

#include "utils.h"

namespace ice
{
    Keyboard::Keyboard() noexcept = default;
    Keyboard::~Keyboard() = default;

    bool Keyboard::is_pressed(Key key) const noexcept
    {
        int numkeys = 0;
        auto keys = SDL_GetKeyboardState(&numkeys);
        assert(keys != nullptr);
        assert(numkeys < static_cast<int>(key));
        return keys[static_cast<int>(key)] == SDL_TRUE;
    }

    rsig::signal<KeyMod, Key>& Keyboard::get_key_down_signal() noexcept
    {
        return key_down_signal;
    }

    rsig::connection Keyboard::on_key_down(const std::function<void(KeyMod, Key)>& cb) noexcept
    {
        return key_down_signal.connect(cb);
    }

    rsig::signal<KeyMod, Key>& Keyboard::get_key_up_signal() noexcept
    {
        return key_up_signal;
    }

    rsig::connection Keyboard::on_key_up(const std::function<void(KeyMod, Key)>& cb) noexcept
    {
        return key_up_signal.connect(cb);
    }

    rsig::signal<const std::string_view>& Keyboard::get_text_signal() noexcept
    {
        return text_signal;
    }

    rsig::connection Keyboard::on_text(const std::function<void(const std::string_view)>& cb) noexcept
    {
        return text_signal.connect(cb);
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

    void Keyboard::handle_event(const SDL_Event& event) const
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
