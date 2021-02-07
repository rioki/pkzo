//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#ifndef _ICE_JOYSICK_H_
#define _ICE_JOYSICK_H_

#include "config.h"

#include <functional>
#include <glm/fwd.hpp>

#include "enums.h"

union SDL_Event;
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

namespace pkzo
{
    class PKZO_EXPORT Joystick
    {
    public:
        Joystick(int id);
        Joystick(const Joystick&) = delete;
        ~Joystick();
        Joystick& operator = (const Joystick&) = delete;

        std::string get_name() const noexcept;
        uint8_t get_axis_count() const noexcept;
        uint8_t get_ball_count() const noexcept;
        uint8_t get_button_count() const noexcept;
        uint8_t get_hat_count() const noexcept;

        void on_axis_motion(const std::function<void (uint8_t, float)>& cb);
        void on_ball_motion(const std::function<void (uint8_t, glm::ivec2)>& cb);
        void on_button_down(const std::function<void (uint8_t)>& cb);
        void on_button_up(const std::function<void (uint8_t)>& cb);
        void on_hat_motion(const std::function<void (uint8_t, glm::ivec2)>& cb);

    private:
        SDL_Joystick* joystick;

        std::function<void (uint8_t, float)>      axis_motion_cb;
        std::function<void (uint8_t, glm::ivec2)> ball_motion_cb;
        std::function<void (uint8_t)>             button_down_cb;
        std::function<void (uint8_t)>             button_up_cb;
        std::function<void (uint8_t, glm::ivec2)> hat_motion_cb;

        void handle_event(const SDL_Event& event) const;

    friend class Main;
    };
}

#endif
