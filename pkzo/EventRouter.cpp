// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

namespace pkzo
{
    EventRouter::EventRouter()
    {
        auto r = SDL_Init(SDL_INIT_VIDEO);
        if (r < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    EventRouter::~EventRouter()
    {
        SDL_Quit();
    }

    rsig::connection EventRouter::on_quit(const std::function<void ()>& cb)
    {
        return quit_signal.connect(cb);
    }

    void EventRouter::disconnect_quit(const rsig::connection& con)
    {
        quit_signal.disconnect(con);
    }

    rsig::connection EventRouter::on_event(const std::function<void (const SDL_Event&)>& cb)
    {
        return event_signal.connect(cb);
    }

    void EventRouter::disconnect_event(const rsig::connection& con)
    {
        event_signal.disconnect(con);
    }

    void EventRouter::inject_quit()
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_QUIT;
        sdl_event.quit.timestamp = SDL_GetTicks();
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_key_down(KeyMod mod, Key key)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_KEYDOWN;
        sdl_event.key.timestamp = SDL_GetTicks();
        sdl_event.key.state = SDL_PRESSED;
        sdl_event.key.repeat = 0;
        sdl_event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        sdl_event.key.keysym.sym = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key));
        sdl_event.key.keysym.mod = static_cast<Uint16>(mod);
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_key_up(KeyMod mod, Key key)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_KEYUP;
        sdl_event.key.timestamp = SDL_GetTicks();
        sdl_event.key.state = SDL_RELEASED;
        sdl_event.key.repeat = 0;
        sdl_event.key.keysym.scancode = static_cast<SDL_Scancode>(key);
        sdl_event.key.keysym.sym = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key));
        sdl_event.key.keysym.mod = static_cast<Uint16>(mod);
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_button_press(const glm::uvec2& position, MouseButton button)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_MOUSEBUTTONDOWN;
        sdl_event.button.button = static_cast<Uint8>(button);
        sdl_event.button.state = SDL_PRESSED;
        sdl_event.button.x = position.x;
        sdl_event.button.y = position.y;
        sdl_event.button.timestamp = SDL_GetTicks();
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_button_release(const glm::uvec2& position, MouseButton button)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_MOUSEBUTTONUP;
        sdl_event.button.button = static_cast<Uint8>(button);
        sdl_event.button.state = SDL_RELEASED;
        sdl_event.button.x = position.x;
        sdl_event.button.y = position.y;
        sdl_event.button.timestamp = SDL_GetTicks();
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_mouse_move(const glm::uvec2& position, const glm::ivec2& delta)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_MOUSEMOTION;
        sdl_event.motion.x = position.x;
        sdl_event.motion.y = position.y;
        sdl_event.motion.xrel = delta.x;
        sdl_event.motion.yrel = delta.y;
        sdl_event.motion.timestamp = SDL_GetTicks();
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::inject_mouse_wheel(const glm::ivec2& scroll)
    {
        auto sdl_event = SDL_Event{};
        sdl_event.type = SDL_MOUSEWHEEL;
        sdl_event.wheel.x = scroll.x;
        sdl_event.wheel.y = scroll.y;
        sdl_event.wheel.timestamp = SDL_GetTicks();
        SDL_PushEvent(&sdl_event);
    }

    void EventRouter::tick()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit_signal.emit();
            }

            event_signal.emit(e);
        }
    }
}
