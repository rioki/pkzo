// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Mouse.h"

#include <cassert>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace pkzo
{
    Mouse::Mouse() = default;

    Mouse::~Mouse() = default;

    void Mouse::show_cursor()
    {
        SDL_ShowCursor(1);
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    void Mouse::hide_cursor()
    {
        SDL_ShowCursor(0);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    bool Mouse::is_cursor_visible() const
    {
        return SDL_ShowCursor(-1) == 1;
    }

    bool Mouse::is_pressed(unsigned int button) const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button)) == SDL_BUTTON(button);
    }

    void Mouse::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                emit(BUTTON_PRESS, glm::uint{event.button.button}, glm::uvec2{event.button.x, event.button.y});
                break;
            case SDL_MOUSEBUTTONUP:
                emit(BUTTON_RELEASE, glm::uint{event.button.button}, glm::uvec2{event.button.x, event.button.y});
                break;
            case SDL_MOUSEWHEEL:
                emit(WHEEL, glm::ivec2{event.wheel.x, event.wheel.y});
                break;
            case SDL_MOUSEMOTION:
                emit(MOVE, glm::ivec2{event.motion.xrel, event.motion.yrel}, glm::uvec2{event.motion.x, event.motion.y});
                break;
            default:
                throw std::logic_error("NOT WITH ME!");
        }
    }
}
