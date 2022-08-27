// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <memory>
#include <vector>

#include "System.h"
#include "SdlSentry.h"

namespace ice
{
    class Mouse;
    class Keyboard;
    class Joystick;

    class ICE_EXPORT InputSystem : public System
    {
    public:
        InputSystem(Engine& e);

        ~InputSystem();

        Mouse* get_mouse() noexcept;
        const Mouse* get_mouse() const noexcept;

        Keyboard* get_keyboard() noexcept;
        const Keyboard* get_keyboard() const noexcept;

        std::vector<Joystick*> get_joysticks() noexcept;
        std::vector<const Joystick*> get_joysticks() const noexcept;

        void tick() override;

    private:
        SdlSentry                              sdl_sentry;

        std::unique_ptr<Mouse>                 mouse;
        std::unique_ptr<Keyboard>              keyboard;
        std::vector<std::unique_ptr<Joystick>> joysticks;
    };
}
