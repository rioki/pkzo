// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <functional>
#include <glm/fwd.hpp>
#include <rsig/rsig.h>

union SDL_Event;
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

namespace ice
{
    class ICE_EXPORT Joystick
    {
    public:
        Joystick(int id);
        ~Joystick();

        std::string get_name() const noexcept;
        uint8_t get_axis_count() const noexcept;
        uint8_t get_ball_count() const noexcept;
        uint8_t get_button_count() const noexcept;
        uint8_t get_hat_count() const noexcept;

        rsig::signal<uint8_t, float>& get_axis_motion_signal() noexcept;
        rsig::connection on_axis_motion(const std::function<void (uint8_t, float)>& cb) noexcept;

        rsig::signal<uint8_t, glm::ivec2>& ball_motion_signa() noexcept;
        rsig::connection on_ball_motion(const std::function<void (uint8_t, glm::ivec2)>& cb) noexcept;

        rsig::signal<uint8_t>& get_button_down_signal() noexcept;
        rsig::connection on_button_down(const std::function<void (uint8_t)>& cb) noexcept;

        rsig::signal<uint8_t>& get_button_up_signal() noexcept;
        rsig::connection on_button_up(const std::function<void (uint8_t)>& cb) noexcept;

        rsig::signal<uint8_t, glm::ivec2>& get_hat_motion_signal() noexcept;
        rsig::connection on_hat_motion(const std::function<void (uint8_t, glm::ivec2)>& cb) noexcept;

    private:
        SDL_Joystick* joystick;

        rsig::signal<uint8_t, float>      axis_motion_signal;
        rsig::signal<uint8_t, glm::ivec2> ball_motion_signal;
        rsig::signal<uint8_t>             button_down_signal;
        rsig::signal<uint8_t>             button_up_signal;
        rsig::signal<uint8_t, glm::ivec2> hat_motion_signal;

        void handle_event(const SDL_Event& event) const;

        Joystick(const Joystick&) = delete;
        Joystick& operator = (const Joystick&) = delete;

    friend class InputSystem;
    };
}
