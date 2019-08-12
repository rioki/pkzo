// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "InputSystem.h"

#include <cassert>
#include <SDL2/SDL.h>

#include "Engine.h"
#include "Window.h"
#include "Mouse.h"
#include "Key.h"
#include "Keyboard.h"

namespace pkzo
{
    InputSystem::InputSystem(Engine& e)
    : engine(e)
    {
        mouse    = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();
    }

    std::shared_ptr<Mouse> InputSystem::get_mouse()
    {
        assert(mouse);
        return mouse;
    }

    std::shared_ptr<Keyboard> InputSystem::get_keyboard()
    {
        assert(keyboard);
        return keyboard;
    }

    void InputSystem::tick(float dt)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
             switch (event.type)
             {
                case SDL_QUIT:
                    engine.get_window().handle_event(event);
                    engine.stop();
                    break;
                case SDL_WINDOWEVENT:
                    engine.get_window().handle_event(event);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    assert(keyboard);
                    keyboard->handle_event(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                case SDL_MOUSEMOTION:
                    assert(mouse);
                    mouse->handle_event(event);
                    break;
                default:
                    /* stfu */
                    break;
             }
        }
    }
}
