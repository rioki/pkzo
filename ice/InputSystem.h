// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <memory>
#include <vector>

#include "System.h"
#include "SdlSentry.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"

namespace ice
{
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

        void inject_mouse_button_down(MouseButton button, glm::ivec2 position);
        void inject_mouse_button_up(MouseButton button, glm::ivec2 position);
        void inject_mouse_move(glm::ivec2 position, glm::ivec2 motion);
        void inject_mouse_wheel(glm::ivec2 motion);

        void inject_key_down(KeyMod mod, Key key);
        void inject_key_up(KeyMod mod, Key key);
        void inject_text(const std::string_view text);

        void tick() override;

    private:
        SdlSentry                              sdl_sentry;

        std::unique_ptr<Mouse>                 mouse;
        std::unique_ptr<Keyboard>              keyboard;
        std::vector<std::unique_ptr<Joystick>> joysticks;
    };
}
