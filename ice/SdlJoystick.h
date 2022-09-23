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

#pragma once
#include "config.h"

#include "Joystick.h"

union SDL_Event;
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

namespace ice
{
    class ICE_EXPORT SdlJoystick : public Joystick
    {
    public:
        SdlJoystick(int id);
        ~SdlJoystick();

        std::string get_name() const noexcept override;
        uint8_t get_axis_count() const noexcept override;
        uint8_t get_ball_count() const noexcept override;
        uint8_t get_button_count() const noexcept override;
        uint8_t get_hat_count() const noexcept override;

        void handle_event(const SDL_Event& event) const;

    private:
        SDL_Joystick* joystick;
    };
}
