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
#include <type_traits>

#include <glm/glm.hpp>
#include <rsig/rsig.h>
#include <SDL2/SDL.h>

#include "defines.h"
#include "enums.h"

namespace pkzo
{
    class EventRouter;

    class PKZO_EXPORT Keyboard
    {
    public:
        Keyboard(EventRouter& event_router);
        ~Keyboard();

        bool is_pressed(Key key) const;

        rsig::connection on_key_press(const std::function<void (KeyMod, Key)>& cb);
        void disconnect_key_press(const rsig::connection& con);

        rsig::connection on_key_release(const std::function<void (KeyMod, Key)>& cb);
        void disconnect_key_release(const rsig::connection& con);

    private:
        EventRouter&      event_router;
        rsig::connection  event_con;
        rsig::signal<KeyMod, Key> key_press_signal;
        rsig::signal<KeyMod, Key> key_release_signal;

        void handle_events(const SDL_Event& ev);

        Keyboard(const Keyboard&) = delete;
        Keyboard& operator = (const Keyboard&) = delete;
    };
}
