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
#include <memory>

#include <glm/glm.hpp>
#include <rsig/rsig.h>
#include <SDL2/SDL.h>

#include "defines.h"
#include "EventRouter.h"

namespace pkzo
{
    enum class WindowMode : Uint32
    {
        STATIC     = 0,
        FULLSCREEN = SDL_WINDOW_FULLSCREEN
    };

    enum class MessageBoxFlags : Uint32
    {
        ERROR       = SDL_MESSAGEBOX_ERROR,
        WARNING     = SDL_MESSAGEBOX_WARNING,
        INFORMATION = SDL_MESSAGEBOX_INFORMATION
    };

    class PKZO_EXPORT Window
    {
    public:
        Window(EventRouter& event_router, const glm::uvec2& size, WindowMode mode, const std::string& title);
        ~Window();

        glm::uvec2 get_size() const;
        glm::uvec2 get_drawable_size() const;
        void set_size(const glm::uvec2& value);

        WindowMode get_mode() const;
        void set_mode(WindowMode mode);

        std::string get_title() const;
        void set_title(const std::string& value);

        rsig::connection on_draw(const std::function<void ()>& cb);
        void disconnect_draw(const rsig::connection& con);

        rsig::connection on_resize(const std::function<void ()>& cb);
        void disconnect_resize(const rsig::connection& con);

        void draw();

    private:
        EventRouter&     event_router;
        rsig::connection event_con;
        SDL_Window*      window    = nullptr;

        rsig::signal<> draw_signal;
        rsig::signal<>  resize_signal;

        void handle_events(const SDL_Event& ev);

        Window(const Window&) = delete;
        Window& operator = (const Window&) = delete;

        friend PKZO_EXPORT void show_message_box(Window& window, MessageBoxFlags flags, const std::string& title, const std::string& text);
    };

    PKZO_EXPORT void show_message_box(MessageBoxFlags flags, const std::string& title, const std::string& text);
    PKZO_EXPORT void show_message_box(Window& window, MessageBoxFlags flags, const std::string& title, const std::string& text);
}

