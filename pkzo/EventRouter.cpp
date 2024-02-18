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

#include "pch.h"
#include "EventRouter.h"

namespace pkzo
{
    rex::connection EventRouter::on_event(const std::function<void(const SDL_Event&)>& cb)
    {
        return event_signal.connect(cb);
    }

    rex::signal<const SDL_Event&>& EventRouter::get_event_signal()
    {
        return event_signal;
    }

    rex::connection EventRouter::on_quit(const std::function<void()>& cb)
    {
        return quit_signal.connect(cb);
    }

    rex::signal<>& EventRouter::get_quit_signal()
    {
        return quit_signal;
    }

    void EventRouter::route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit_signal.emit();
                break;
            default:
                event_signal.emit(event);
                break;
            }
        }
    }
}
