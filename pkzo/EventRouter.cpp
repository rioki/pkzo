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

#include "EventRouter.h"

namespace pkzo
{
    EventRouter::EventRouter() noexcept
    {
        auto r = SDL_Init(SDL_INIT_VIDEO);
        if (r < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    EventRouter::~EventRouter()
    {
        SDL_Quit();
    }

    rsig::connection EventRouter::on_quit(const std::function<void ()>& cb)
    {
        return quit_signal.connect(cb);
    }

    void EventRouter::disconnect_quit(const rsig::connection& con)
    {
        quit_signal.disconnect(con);
    }

    rsig::connection EventRouter::on_event(const std::function<void (const SDL_Event&)>& cb)
    {
        return event_signal.connect(cb);
    }

    void EventRouter::disconnect_event(const rsig::connection& con)
    {
        event_signal.disconnect(con);
    }

    void EventRouter::tick()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit_signal.emit();
            }

            event_signal.emit(e);
        }
    }
}
