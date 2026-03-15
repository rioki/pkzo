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

#pragma once

#include <functional>

#include <rsig/rsig.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <pkzo/pkzo.h>

#include "api.h"

namespace pkzo
{
    enum class MouseButton : Uint8
    {
        LEFT    = SDL_BUTTON_LEFT,
        MIDDLE  = SDL_BUTTON_MIDDLE,
        RIGHT   = SDL_BUTTON_RIGHT,
        BUTTON4 = SDL_BUTTON_X1,
        BUTTON5 = SDL_BUTTON_X2
    };

    struct MouseMoveEvent
    {
        glm::uvec2 position;
        glm::ivec2 releative;
    };

    struct MouseButtonDownEvent
    {
        glm::uvec2 position;
        MouseButton button;
    };

    struct MouseButtonUpEvent
    {
        glm::uvec2 position;
        MouseButton button;
    };

    struct MouseWheelEvent
    {
        glm::ivec2 releative;
    };

    using InputEvent = pkzo::InputEvent;

    //! Install an observer for the quit event.
    //!
    //! The quit event is issued when either the last window is closed or
    //! the operating system requests the application to terminate.
    PKZO_EXPORT rsig::connection on_quit(const std::function<void ()>& handler);

    //! Distribute all pending OS events to the different consumers.
    PKZO_EXPORT void rotue_events();
}
