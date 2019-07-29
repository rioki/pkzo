// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Keyboard.h"

#include <algorithm>
#include <stdexcept>
#include <string_view>
#include <SDL2/SDL.h>

namespace pkzo
{
    Keyboard::Keyboard()
    {
        SDL_StartTextInput();
    }

    Keyboard::~Keyboard()
    {
        SDL_StopTextInput();
    }

    bool Keyboard::is_pressed(Key key) const
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        return state[key] == 1;
    }

    void Keyboard::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                emit(KEY_PRESS, static_cast<Key>(event.key.keysym.scancode));
                break;
            case SDL_KEYUP:
                emit(KEY_RELEASE, static_cast<Key>(event.key.keysym.scancode));
                break;
            case SDL_TEXTINPUT:
                emit(TEXT, std::string_view{event.text.text});
                break;
            case SDL_TEXTEDITING:
                // handled by window
                break;
            default:
                throw std::logic_error("ARE YOU INSANE!");
        }
    }
}
