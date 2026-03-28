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

#include "api.h"
#include "events.h"
#include "SdlSentry.h"

namespace pkzo
{
    class PKZO_EXPORT Mouse
    {
    public:
        Mouse();

        ~Mouse();

        rsig::connection on_move(const std::function<void (MouseMoveEvent)>& handler);
        rsig::connection on_button_down(const std::function<void (MouseButtonDownEvent)>& handler);
        rsig::connection on_button_up(const std::function<void (MouseButtonUpEvent)>& handler);
        rsig::connection on_wheel(const std::function<void (MouseWheelEvent)>& handler);

    private:
        SdlSentry sdl_sentry = SdlSentry{SdlSubsystem::EVENTS};

        rsig::slot                         input_slot;

        rsig::signal<MouseMoveEvent>       move_signal;
        rsig::signal<MouseButtonDownEvent> button_down_signal;
        rsig::signal<MouseButtonUpEvent>   button_up_signal;
        rsig::signal<MouseWheelEvent>      wheel_signal;

        Mouse(const Mouse&) = delete;
        Mouse& operator = (const Mouse&) = delete;
    };
}
