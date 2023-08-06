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

#pragma once
#include "config.h"

#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_events.h>
#include <glm/glm.hpp>
#include <rsig/rsig.h>

namespace pkzo
{
    class EventRouter;

    enum class MouseButton
    {
        NONE    = 0,
        LEFT    = SDL_BUTTON_LEFT,
        MIDDLE  = SDL_BUTTON_MIDDLE,
        RIGHT   = SDL_BUTTON_RIGHT,
        BUTTON4 = SDL_BUTTON_X1,
        BUTTON5 = SDL_BUTTON_X2
    };

    class PKZO_EXPORT Mouse
    {
    public:
        Mouse(EventRouter& router);
        ~Mouse();

        bool is_pressed(MouseButton button) const noexcept;

        void set_cursor_visible(bool value) noexcept;
        bool get_cursor_visible() const noexcept;
        glm::ivec2 get_cursor_position() const noexcept;

        rsig::signal<MouseButton, glm::ivec2>& get_button_press_signal() noexcept;
        rsig::signal<MouseButton, glm::ivec2>& get_button_release_signal() noexcept;
        rsig::signal<glm::ivec2, glm::ivec2>&  get_move_signal() noexcept;
        rsig::signal<glm::ivec2>&              get_wheel_signal() noexcept;

    private:
        EventRouter&     router;
        rsig::connection router_connection;

        rsig::signal<MouseButton, glm::ivec2> button_press_signal;
        rsig::signal<MouseButton, glm::ivec2> button_release_signal;
        rsig::signal<glm::ivec2, glm::ivec2>  move_signal;
        rsig::signal<glm::ivec2>              wheel_signal;

        void handle_events(const SDL_Event& event);
    };
}
