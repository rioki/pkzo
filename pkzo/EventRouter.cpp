// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "EventRouter.h"

#include <SDL2/SDL_timer.h>

namespace pkzo
{
    EventRouter::EventRouter() = default;
    EventRouter::~EventRouter() = default;

    rsig::signal<const SDL_Event&>& EventRouter::get_event_signal() noexcept
    {
        return event_signal;
    }

    void EventRouter::inject_key_press(KeyMod mod, Key key) noexcept
    {
        auto event = SDL_Event{SDL_KEYDOWN};
        event.key.keysym.mod      = static_cast<Uint16>(mod);
        event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        event.key.keysym.sym      = SDL_GetKeyFromScancode(event.key.keysym.scancode);
        event.key.timestamp       = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::inject_key_release(KeyMod mod, Key key) noexcept
    {
        auto event = SDL_Event{SDL_KEYUP};
        event.key.keysym.mod      = static_cast<Uint16>(mod);
        event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        event.key.keysym.sym      = SDL_GetKeyFromScancode(event.key.keysym.scancode);
        event.key.timestamp       = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::inject_mouse_move(glm::ivec2 pos, glm::ivec2 rel) noexcept
    {
        auto event = SDL_Event{SDL_MOUSEMOTION};
        event.motion.x            = pos.x;
        event.motion.y            = pos.y;
        event.motion.xrel         = rel.x;
        event.motion.yrel         = rel.y;
        event.button.timestamp    = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::inject_mouse_button_press(MouseButton button, glm::ivec2 pos) noexcept
    {
        auto event = SDL_Event{SDL_MOUSEBUTTONDOWN};
        event.button.button       = static_cast<Uint8>(button);
        event.button.x            = pos.x;
        event.button.y            = pos.y;
        event.button.timestamp    = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::inject_mouse_button_release(MouseButton button, glm::ivec2 pos) noexcept
    {
        auto event = SDL_Event{SDL_MOUSEBUTTONUP};
        event.button.button       = static_cast<Uint8>(button);
        event.button.x            = pos.x;
        event.button.y            = pos.y;
        event.button.timestamp    = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::inject_mouse_wheel( glm::ivec2 rel) noexcept
    {
        auto event = SDL_Event{SDL_MOUSEWHEEL};
        event.wheel.x          = rel.x;
        event.wheel.y          = rel.y;
        event.button.timestamp = SDL_GetTicks();
        SDL_PushEvent(&event);
    }

    void EventRouter::route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            event_signal.emit(event);
        }
    }
}
