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

        [[nodiscard]]
        Mouse* get_mouse() noexcept;
        [[nodiscard]]
        const Mouse* get_mouse() const noexcept;

        [[nodiscard]]
        Keyboard* get_keyboard() noexcept;
        [[nodiscard]]
        const Keyboard* get_keyboard() const noexcept;

        [[nodiscard]]
        std::vector<Joystick*> get_joysticks() noexcept;
        [[nodiscard]]
        std::vector<const Joystick*> get_joysticks() const noexcept;

        void tick() override;

    private:
        SdlSentry                              sdl_sentry;

        std::unique_ptr<Mouse>                 mouse;
        std::unique_ptr<Keyboard>              keyboard;
        std::vector<std::unique_ptr<Joystick>> joysticks;
    };
}
