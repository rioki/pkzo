// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Mouse.h"

#include "utils.h"

namespace ice
{
    Mouse::Mouse() noexcept = default;
    Mouse::~Mouse() = default;

    void Mouse::set_cursor_visible(bool value) noexcept
    {
        if (value)
        {
            SDL_ShowCursor(SDL_TRUE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
        else
        {
            SDL_ShowCursor(SDL_FALSE);
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }

    bool Mouse::get_cursor_visible() const noexcept
    {
        return SDL_ShowCursor(SDL_QUERY) == SDL_TRUE;
    }

    glm::ivec2 Mouse::get_cursor_position() const noexcept
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return {x, y};
    }

    rsig::signal<MouseButton, glm::ivec2>& Mouse::get_button_down_signal() noexcept
    {
        return button_down_signal;
    }

    rsig::connection Mouse::on_button_down(const std::function<void(MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_down_signal.connect(cb);
    }

    rsig::signal<MouseButton, glm::ivec2>& Mouse::get_button_up_signal() noexcept
    {
        return button_up_signal;
    }

    rsig::connection Mouse::on_button_up(const std::function<void(MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_up_signal.connect(cb);
    }

    rsig::signal<glm::ivec2, glm::ivec2>& Mouse::get_move_signal() noexcept
    {
        return move_signal;
    }

    rsig::connection Mouse::on_move(const std::function<void(glm::ivec2, glm::ivec2)>& cb) noexcept
    {
        return move_signal.connect(cb);
    }

    rsig::signal<glm::ivec2>& Mouse::get_wheel_signal() noexcept
    {
        return wheel_signal;
    }

    rsig::connection Mouse::on_wheel(const std::function<void(glm::ivec2)>& cb) noexcept
    {
        return wheel_signal.connect(cb);
    }

    void Mouse::handle_event(const SDL_Event& event) const
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            move_signal.emit({event.motion.x, event.motion.y}, {event.motion.xrel, event.motion.yrel});
            break;
        case SDL_MOUSEBUTTONDOWN:
            button_down_signal.emit(MouseButton(event.button.button), {event.button.x, event.button.y});
            break;
        case SDL_MOUSEBUTTONUP:
            button_up_signal.emit(MouseButton(event.button.button), {event.button.x, event.button.y});
            break;
        case SDL_MOUSEWHEEL:
            wheel_signal.emit({event.wheel.x, event.wheel.y});
            break;
        default:
            assert(false);
            break;
        }
    }
}
