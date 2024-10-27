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
#include <glm/glm.hpp>

#include "defines.h"
#include "enums.h"

namespace pkzo
{
    enum class Key;

    class PKZO_EXPORT EventRouter
    {
    public:
        EventRouter();
        ~EventRouter();

        rsig::connection on_quit(const std::function<void ()>& cb);
        void disconnect_quit(const rsig::connection& con);

        rsig::connection on_event(const std::function<void (const SDL_Event&)>& cb);
        void disconnect_event(const rsig::connection& con);

        void tick();

        void inject_quit();
        void inject_key_down(KeyMod mod, Key key);
        void inject_key_up(KeyMod mod, Key key);
        void inject_button_press(const glm::uvec2& position, MouseButton button);
        void inject_button_release(const glm::uvec2& position, MouseButton button);
        void inject_mouse_move(const glm::uvec2& position, const glm::ivec2& delta);
        void inject_mouse_wheel(const glm::ivec2& scroll);

    private:
        rsig::signal<> quit_signal;
        rsig::signal<const SDL_Event&> event_signal;

        EventRouter(const EventRouter&) = delete;
        EventRouter& operator = (const EventRouter&) = delete;
    };
}
