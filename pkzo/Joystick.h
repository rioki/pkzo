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

#include <SDL2/SDL_events.h>
#include <glm/glm.hpp>
#include <rsig/rsig.h>

#include "SdlInit.h"

namespace pkzo
{
    class EventRouter;

    class PKZO_EXPORT Joystick
    {
    public:
        static unsigned int get_joystick_count();

        Joystick(EventRouter& router, int id);
        ~Joystick();

        std::string get_name() const noexcept;
        uint8_t get_axis_count() const noexcept;
        uint8_t get_ball_count() const noexcept;
        uint8_t get_button_count() const noexcept;
        uint8_t get_hat_count() const noexcept;

        rsig::signal<uint8_t, float>& get_axis_motion_signal() noexcept;
        rsig::signal<uint8_t, glm::ivec2>& get_ball_motion_signal() noexcept;
        rsig::signal<uint8_t>& get_button_down_signal() noexcept;
        rsig::signal<uint8_t>& get_button_up_signal() noexcept;
        rsig::signal<uint8_t, glm::ivec2>& get_hat_motion_signal() noexcept;

    private:
        EventRouter&     router;
        rsig::connection router_connection;

        SDL_Joystick* joystick;

        rsig::signal<uint8_t, float>      axis_motion_signal;
        rsig::signal<uint8_t, glm::ivec2> ball_motion_signal;
        rsig::signal<uint8_t>             button_down_signal;
        rsig::signal<uint8_t>             button_up_signal;
        rsig::signal<uint8_t, glm::ivec2> hat_motion_signal;

        void handle_events(const SDL_Event& event);
    };
}
