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

#include "Mouse.h"

#include "stdex.h"
#include "EventRouter.h"

namespace pkzo
{
    Mouse::Mouse(EventRouter& event_router)
    : event_router(event_router)
    {
        event_con = event_router.on_event(rsig::mem_fun(this, &Mouse::handle_events));
    }

    Mouse::~Mouse()
    {
        event_router.disconnect_event(event_con);
    }

    bool Mouse::is_pressed(MouseButton button) const
    {
        auto btn = SDL_BUTTON(static_cast<unsigned int>(button));
        return (SDL_GetMouseState(nullptr, nullptr) & btn) == btn;
    }

    void Mouse::set_cursor_visible(bool value)
    {
        SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
    }

    bool Mouse::get_cursor_visible() const
    {
        return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    glm::ivec2 Mouse::get_cursor_position() const
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return {x, y};
    }

    rsig::connection Mouse::on_button_press(const std::function<void (glm::uvec2, MouseButton)>& cb)
    {
        return button_press_signal.connect(cb);
    }

    void Mouse::disconnect_button_press(const rsig::connection& con)
    {
        return button_press_signal.disconnect(con);
    }

    rsig::connection Mouse::on_button_release(const std::function<void (glm::uvec2, MouseButton)>& cb)
    {
        return button_release_signal.connect(cb);
    }

    void Mouse::disconnect_button_release(const rsig::connection& con)
    {
        return button_release_signal.disconnect(con);
    }

    rsig::connection Mouse::on_move(const std::function<void (glm::uvec2, glm::ivec2)>& cb)
    {
        return move_signal.connect(cb);
    }

    void Mouse::disconnect_move(const rsig::connection& con)
    {
        return move_signal.disconnect(con);
    }

    rsig::connection Mouse::on_wheel(const std::function<void (glm::ivec2)>& cb)
    {
        return wheel_signal.connect(cb);
    }

    void Mouse::disconnect_wheel(const rsig::connection& con)
    {
        return wheel_signal.disconnect(con);
    }

    void Mouse::handle_events(const SDL_Event& ev)
    {
        switch (ev.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                button_press_signal.emit({ ev.button.x, ev.button.y }, static_cast<MouseButton>(ev.button.button));
                break;
            case SDL_MOUSEBUTTONUP:
                button_release_signal.emit({ ev.button.x, ev.button.y }, static_cast<MouseButton>(ev.button.button));
                break;
            case SDL_MOUSEMOTION:
                move_signal.emit({ ev.motion.x, ev.motion.y }, { ev.motion.xrel, ev.motion.yrel });
                break;
            case SDL_MOUSEWHEEL:
                wheel_signal.emit({ ev.wheel.x, ev.wheel.y });
                break;
        }
    }
}
