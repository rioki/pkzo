

// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "SdlSentry.h"

#include <stdexcept>
#include <SDL3/SDL.h>

namespace pkzo
{
    SDL_InitFlags to_sdl_flags(SdlSubsystem s)
    {
        using enum SdlSubsystem;

        auto out = SDL_InitFlags{0};
        if ((s & AUDIO)    == AUDIO)    out |= SDL_INIT_AUDIO;
        if ((s & VIDEO)    == VIDEO)    out |= SDL_INIT_VIDEO;
        if ((s & JOYSTICK) == JOYSTICK) out |= SDL_INIT_JOYSTICK;
        if ((s & HAPTIC)   == HAPTIC)   out |= SDL_INIT_HAPTIC;
        if ((s & GAMEPAD)  == GAMEPAD)  out |= SDL_INIT_GAMEPAD;
        if ((s & EVENTS)   == EVENTS)   out |= SDL_INIT_EVENTS;
        if ((s & SENSOR)   == SENSOR)   out |= SDL_INIT_SENSOR;
        if ((s & CAMERA)   == CAMERA)   out |= SDL_INIT_CAMERA;

        return out;
    }

    SdlSentry::SdlSentry(SdlSubsystem s)
    : subsystem(s)
    {
        auto result = SDL_InitSubSystem(std::to_underlying(subsystem));
        if (result == false)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    SdlSentry::~SdlSentry()
    {
        SDL_QuitSubSystem(std::to_underlying(subsystem));
    }
}
