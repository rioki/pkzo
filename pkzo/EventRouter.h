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

#include <SDL2/SDL.h>

#include <rex/signal.h>

#include "defines.h"
#include "SdlInit.h"

namespace pkzo
{
    class PKZO_EXPORT EventRouter
    {
    public:
        EventRouter() noexcept = default;
        ~EventRouter() = default;

        rex::connection on_event(const std::function<void(const SDL_Event&)>& cb);
        rex::signal<const SDL_Event&>& get_event_signal();

        rex::connection on_quit(const std::function<void()>& cb);
        rex::signal<>& get_quit_signal();

        void route_events();

    private:
        SdlInit sdl_init;
        rex::signal<const SDL_Event&> event_signal;
        rex::signal<>                 quit_signal;
    };
}
