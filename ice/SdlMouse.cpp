// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "SdlMouse.h"

#include <SDL2/SDL.h>

namespace ice
{
    void SdlMouse::set_cursor_visible(bool value) noexcept
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

    bool SdlMouse::get_cursor_visible() const noexcept
    {
        return SDL_ShowCursor(SDL_QUERY) == SDL_TRUE;
    }

    glm::ivec2 SdlMouse::get_cursor_position() const noexcept
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return {x, y};
    }

    void SdlMouse::handle_event(const SDL_Event& event) const
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
