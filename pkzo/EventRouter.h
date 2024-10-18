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

#pragma once

#include <functional>

#include <SDL2/SDL.h>
#include <rsig/rsig.h>

#include "defines.h"

namespace pkzo
{
    class PKZO_API EventRouter
    {
    public:
        EventRouter() noexcept;
        ~EventRouter();

        rsig::connection on_quit(const std::function<void ()>& cb);
        void disconnect_quit(const rsig::connection& con);

        rsig::connection on_event(const std::function<void (const SDL_Event&)>& cb);
        void disconnect_event(const rsig::connection& con);

        void tick();

    private:
        rsig::signal<> quit_signal;
        rsig::signal<const SDL_Event&> event_signal;

        EventRouter(const EventRouter&) = delete;
        EventRouter& operator = (const EventRouter&) = delete;
    };
}
