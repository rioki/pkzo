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

#include <rsig/rsig.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_events.h>

#include "SdlInit.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace pkzo
{
    //! Input Event Router
    //!
    //! The EventRouter captures the OS's input and routes it to input consumers
    //! like Mouse, Keyboard or Joystick.
    class PKZO_EXPORT EventRouter
    {
    public:
        EventRouter();
        EventRouter(const EventRouter&) = delete;
        ~EventRouter();
        EventRouter& operator = (const EventRouter&) = delete;

        // Implementation Defined
        rsig::signal<const SDL_Event&>& get_event_signal() noexcept;

        //! Quit Signel
        //!
        //! Handle the event when the OS request the application to close
        //! such as closing the primary window, ALT+F4 or program termination.
        rsig::signal<>& get_quit_signal() noexcept;

        //! Inject input
        //!
        //! @{
        void inject_quit() noexcept;
        void inject_key_press(KeyMod mod, Key key) noexcept;
        void inject_key_release(KeyMod mod, Key key) noexcept;
        void inject_mouse_move(glm::ivec2 pos, glm::ivec2 rel) noexcept;
        void inject_mouse_button_press(MouseButton button, glm::ivec2 pos) noexcept;
        void inject_mouse_button_release(MouseButton button, glm::ivec2 pos) noexcept;
        void inject_mouse_wheel(glm::ivec2 rel) noexcept;
        void inject_window_resize(glm::uvec2 size) noexcept;
        //! @}

        //! Rotue the events.
        void route_events();

    private:
        SdlInit sdl_init;

        rsig::signal<const SDL_Event&> event_signal;
        rsig::signal<>                 quit_signal;
    };
}

