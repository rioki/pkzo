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

    void InputSystem::inject_mouse_button_down(MouseButton button, glm::ivec2 position)
    {
        SDL_Event event;
        event.type             = SDL_MOUSEBUTTONDOWN;
        event.button.type      = SDL_MOUSEBUTTONDOWN;
        event.button.timestamp = SDL_GetTicks();
        event.button.button    = static_cast<Uint8>(button);
        event.button.x         = position.x;
        event.button.y         = position.y;
        SDL_PushEvent(&event);
    }

    void InputSystem::inject_mouse_button_up(MouseButton button, glm::ivec2 position)
    {
        SDL_Event event;
        event.type             = SDL_MOUSEBUTTONUP;
        event.button.type      = SDL_MOUSEBUTTONUP;
        event.button.timestamp = SDL_GetTicks();
        event.button.button    = static_cast<Uint8>(button);
        event.button.x         = position.x;
        event.button.y         = position.y;
        SDL_PushEvent(&event);
    }

    void InputSystem::inject_mouse_move(glm::ivec2 position, glm::ivec2 motion)
    {
        SDL_Event event;
        event.type             = SDL_MOUSEMOTION;
        event.motion.type      = SDL_MOUSEMOTION;
        event.motion.timestamp = SDL_GetTicks();
        event.motion.x         = position.x;
        event.motion.y         = position.y;
        event.motion.xrel      = motion.x;
        event.motion.yrel      = motion.y;
        SDL_PushEvent(&event);
    }

    void InputSystem::inject_mouse_wheel(glm::ivec2 motion)
    {
        SDL_Event event;
        event.type            = SDL_MOUSEWHEEL;
        event.wheel.type      = SDL_MOUSEWHEEL;
        event.wheel.timestamp = SDL_GetTicks();
        event.wheel.x         = motion.x;
        event.wheel.y         = motion.y;
        SDL_PushEvent(&event);
    }

    Uint16 mode2sdl(KeyMod mod)
    {
        Uint16 result = 0u;

        if ((mod & KeyMod::SHIFT) == KeyMod::SHIFT)
        {
            result |= KMOD_SHIFT;
        }
        if ((mod & KeyMod::CTRL) == KeyMod::CTRL)
        {
            result |= KMOD_CTRL;
        }
        if ((mod & KeyMod::ALT) == KeyMod::ALT)
        {
            result |= KMOD_ALT;
        }
        if ((mod & KeyMod::META) == KeyMod::META)
        {
            result |= KMOD_GUI;
        }
        return result;
    }

    void InputSystem::inject_key_down(KeyMod mod, Key key)
    {
        SDL_Event event;
        event.type                = SDL_KEYDOWN;
        event.key.type            = SDL_KEYDOWN;
        event.key.timestamp       = SDL_GetTicks();
        event.key.keysym.mod      = mode2sdl(mod);
        event.key.keysym.sym      = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key));
        event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        SDL_PushEvent(&event);
    }

    void InputSystem::inject_key_up(KeyMod mod, Key key)
    {
        SDL_Event event;
        event.type                = SDL_KEYUP;
        event.key.type            = SDL_KEYUP;
        event.key.timestamp       = SDL_GetTicks();
        event.key.keysym.mod      = mode2sdl(mod);
        event.key.keysym.sym      = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key));
        event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        SDL_PushEvent(&event);
    }

    void InputSystem::inject_text(const std::string_view text)
    {
        SDL_Event event;
        event.type           = SDL_TEXTINPUT;
        event.text.type      = SDL_TEXTINPUT;
        event.text.timestamp = SDL_GetTicks();
        strncpy_s(event.text.text, SDL_TEXTINPUTEVENT_TEXT_SIZE, text.data(), text.size());
        SDL_PushEvent(&event);
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
