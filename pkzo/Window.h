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

#include <string_view>
#include <iostream>
#include <functional>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "defines.h"
#include "Image.h"
#include "EventRouter.h"

namespace pkzo
{
    enum class WindowMode
    {
        WINDOWED,
        FULLSCREEN,
        FULLSCREEN_DESKTOP
    };

    PKZO_EXPORT std::ostream& operator << (std::ostream& os, WindowMode mode );

    class PKZO_EXPORT Window
    {
    public:
        Window(EventRouter& er, const std::string_view& title, glm::uvec2 size, WindowMode mode = pkzo::WindowMode::WINDOWED);
        Window(EventRouter& er, const std::string_view& title, glm::ivec2 position, glm::uvec2 size, WindowMode mode = pkzo::WindowMode::WINDOWED);
        ~Window();

        std::string_view get_title() const noexcept;
        glm::uvec2 get_size() const noexcept;
        glm::uvec2 get_drawable_size() const noexcept;
        glm::ivec2 get_position() const noexcept;
        WindowMode get_window_mode() const noexcept;

        void set_video_mode(glm::uvec2 size, WindowMode mode);
        void set_position(glm::ivec2 position);

        void init(const std::function<void()>& cb);

        void on_draw(const std::function<void()>& cb);
        void draw();

        Image get_screenshot() const;

    private:
        EventRouter&          event_router;
        SDL_Window*           window    = nullptr;
        SDL_GLContext         glcontext = nullptr;
        std::function<void()> draw_cb;

        void handle_event(const SDL_Event& event);

        Window(const Window&) = delete;
        Window& operator = (const Window&) = delete;
    };
}
