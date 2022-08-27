// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <functional>
#include <glm/fwd.hpp>
#include <rsig/rsig.h>

union SDL_Event;

namespace ice
{
    enum class MouseButton
    {
        NONE,
        LEFT,
        MIDDLE,
        RIGHT,
        BUTTON4,
        BUTTON5
    };

    class ICE_EXPORT Mouse
    {
    public:
        Mouse() noexcept;
        ~Mouse();

        void set_cursor_visible(bool value) noexcept;
        bool get_cursor_visible() const noexcept;

        glm::ivec2 get_cursor_position() const noexcept;

        rsig::signal<MouseButton, glm::ivec2>& get_button_down_signal() noexcept;
        rsig::connection on_button_down(const std::function<void (MouseButton, glm::ivec2)>& cb) noexcept;

        rsig::signal<MouseButton, glm::ivec2>& get_button_up_signal() noexcept;
        rsig::connection on_button_up(const std::function<void (MouseButton, glm::ivec2)>& cb) noexcept;

        rsig::signal<glm::ivec2, glm::ivec2>& get_move_signal() noexcept;
        rsig::connection on_move(const std::function<void (glm::ivec2, glm::ivec2)>& cb) noexcept;

        rsig::signal<glm::ivec2>& get_wheel_signal() noexcept;
        rsig::connection on_wheel(const std::function<void (glm::ivec2)>& cb) noexcept;

    private:
        rsig::signal<MouseButton, glm::ivec2> button_down_signal;
        rsig::signal<MouseButton, glm::ivec2> button_up_signal;
        rsig::signal<glm::ivec2, glm::ivec2>  move_signal;
        rsig::signal<glm::ivec2>              wheel_signal;

        void handle_event(const SDL_Event& event) const;

        Mouse(const Mouse&) = delete;
        Mouse& operator = (const Mouse&) = delete;

    friend class InputSystem;
    };
}
