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

#include "pch.h"
#include "Joystick.h"

namespace pkzo
{
    Joystick::Joystick(int id)
    {
        joystick = SDL_JoystickOpen(id);
        if (joystick == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Joystick::~Joystick()
    {
        SDL_JoystickClose(joystick);
    }

    std::string Joystick::get_name() const noexcept
    {
        auto str = SDL_JoystickName(joystick);
        if (str != nullptr)
        {
            return str;
        }
        else
        {
            return {};
        }
    }

    uint8_t Joystick::get_axis_count() const noexcept
    {
        return SDL_JoystickNumAxes(joystick);
    }

    uint8_t Joystick::get_ball_count() const noexcept
    {
        return SDL_JoystickNumBalls(joystick);
    }

    uint8_t Joystick::get_button_count() const noexcept
    {
        return SDL_JoystickNumButtons(joystick);
    }

    uint8_t Joystick::get_hat_count() const noexcept
    {
        return SDL_JoystickNumHats(joystick);
    }

    void Joystick::on_axis_motion(const std::function<void(uint8_t, float)>& cb)
    {
        axis_motion_cb = cb;
    }

    void Joystick::on_ball_motion(const std::function<void(uint8_t, glm::ivec2)>&cb)
    {
        ball_motion_cb = cb;
    }

    void Joystick::on_button_down(const std::function<void(uint8_t)>&cb)
    {
        button_down_cb = cb;
    }

    void Joystick::on_button_up(const std::function<void(uint8_t)>&cb)
    {
        button_up_cb = cb;
    }

    void Joystick::on_hat_motion(const std::function<void(uint8_t, glm::ivec2)>&cb)
    {
        hat_motion_cb = cb;
    }

    void Joystick::handle_event(const SDL_Event& event) const
    {
        auto id = SDL_JoystickInstanceID(joystick);

        switch (event.type)
        {
        case SDL_JOYAXISMOTION:
            if (event.jaxis.which == id && axis_motion_cb)
            {
                axis_motion_cb(event.jaxis.axis, static_cast<float>(event.jaxis.value) / 32767.0f);
            }
            break;
        case SDL_JOYBALLMOTION:
            if (event.jball.which == id && ball_motion_cb)
            {
                ball_motion_cb(event.jball.ball, {event.jball.xrel, event.jball.yrel});
            }
            break;
        case SDL_JOYBUTTONDOWN:
            if (event.jbutton.which == id && button_down_cb)
            {
                button_down_cb(event.jbutton.button);
            }
            break;
        case SDL_JOYBUTTONUP:
            if (event.jbutton.which == id && button_up_cb)
            {
                button_up_cb(event.jbutton.button);
            }
            break;
        case SDL_JOYHATMOTION:
            if (event.jhat.which == id && hat_motion_cb)
            {
                auto dir = glm::ivec2(0);
                switch (event.jhat.value)
                {
                    case SDL_HAT_LEFTUP:
                        dir = {-1, 1};
                        break;
                    case SDL_HAT_UP:
                        dir = {0, 1};
                        break;
                    case SDL_HAT_RIGHTUP:
                        dir = {1, 1};
                        break;
                    case SDL_HAT_LEFT:
                        dir = {-1, 0};
                        break;
                    case SDL_HAT_CENTERED:
                        dir = {0, 0};
                        break;
                    case SDL_HAT_RIGHT:
                        dir = {1, 0};
                        break;
                    case SDL_HAT_LEFTDOWN:
                        dir = {-1, -1};
                        break;
                    case SDL_HAT_DOWN:
                        dir = {0, -1};
                        break;
                    case SDL_HAT_RIGHTDOWN:
                        dir = {1, -1};
                        break;
                    default:
                        assert(false);
                        break;
                }
                hat_motion_cb(event.jhat.hat, dir);
            }
            break;
        default:
            assert(false);
            break;
        }
    }
}
