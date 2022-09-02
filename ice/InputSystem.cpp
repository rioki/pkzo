// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "InputSystem.h"

#include "Engine.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"

namespace ice
{
    InputSystem::InputSystem(Engine& e)
    : System(e)
    {
        mouse    = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();

        auto jn = SDL_NumJoysticks();
        for (auto j = 0; j < jn; j++)
        {
            joysticks.push_back(std::make_unique<Joystick>(j));
        }
    }

    InputSystem::~InputSystem() = default;

    Mouse* InputSystem::get_mouse() noexcept
    {
        assert(mouse);
        return mouse.get();
    }

    const Mouse* InputSystem::get_mouse() const noexcept
    {
        assert(mouse);
        return mouse.get();
    }

    Keyboard* InputSystem::get_keyboard() noexcept
    {
        assert(keyboard);
        return keyboard.get();
    }

    const Keyboard* InputSystem::get_keyboard() const noexcept
    {
        assert(keyboard);
        return keyboard.get();
    }

    std::vector<Joystick*> InputSystem::get_joysticks() noexcept
    {
        auto result = std::vector<Joystick*>(joysticks.size());
        std::transform(begin(joysticks), end(joysticks), begin(result), [] (auto& uptr) {
            return uptr.get();
        });
        return result;
    }

    std::vector<const Joystick*> InputSystem::get_joysticks() const noexcept
    {
        auto result = std::vector<const Joystick*>(joysticks.size());
        std::transform(begin(joysticks), end(joysticks), begin(result), [] (auto& uptr) {
            return uptr.get();
        });
        return result;
    }

    void InputSystem::tick()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    // TODO allow to veto quit
                    engine.stop();
                    break;
                }
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                    assert(mouse);
                    mouse->handle_event(event);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                    assert(keyboard);
                    keyboard->handle_event(event);
                    break;
                case SDL_JOYAXISMOTION:
                case SDL_JOYBALLMOTION:
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                case SDL_JOYHATMOTION:
                    for (const auto& joystick : joysticks)
                    {
                        assert(joystick);
                        joystick->handle_event(event);
                    }
                    break;
                case SDL_JOYDEVICEADDED:
                case SDL_JOYDEVICEREMOVED:
                    // TODO
                    break;
                default:
                    // do nothing
                    break;
            }
        }
    }
}
