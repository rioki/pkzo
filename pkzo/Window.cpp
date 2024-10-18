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

#include "Window.h"

#include "stdex.h"

namespace pkzo
{
    Window::Window(EventRouter& event_router, const glm::uvec2& size, WindowMode mode, const std::string& title)
    : event_router(event_router)
    {
        event_con = event_router.on_event(rsig::mem_fun(this, &Window::handle_events));

        auto flags = stdex::to_underlying(mode) | SDL_WINDOW_OPENGL;
        window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Window::~Window()
    {
        SDL_DestroyWindow(window);

        event_router.disconnect_event(event_con);
    }

    glm::uvec2 Window::get_size() const
    {
        int x, y;
        SDL_GetWindowSize(window, &x, &y);
        return {x, y};
    }

    glm::uvec2 Window::get_drawable_size() const
    {
        int x, y;
        SDL_GL_GetDrawableSize(window, &x, &y);
        return {x, y};
    }

    void Window::set_size(const glm::uvec2& value)
    {
        SDL_SetWindowSize(window, value.x, value.y);
    }

    WindowMode Window::get_mode() const
    {
        auto flags = SDL_GetWindowFlags(window);

        if ((flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
        {
            return WindowMode::FULLSCREEN;
        }
        else
        {
            return WindowMode::STATIC;
        }
    }

    void Window::set_mode(WindowMode mode)
    {
        SDL_SetWindowFullscreen(window, stdex::to_underlying(mode));
    }

    std::string Window::get_title() const
    {
        auto result = SDL_GetWindowTitle(window);
        return result == nullptr ? "" : result;
    }

    void Window::set_title(const std::string& value)
    {
        SDL_SetWindowTitle(window, value.data());
    }

    rsig::connection Window::on_draw(const std::function<void ()>& cb)
    {
        return draw_signal.connect(cb);
    }

    void Window::disconnect_draw(const rsig::connection& con)
    {
        return draw_signal.disconnect(con);
    }

    rsig::connection Window::on_resize(const std::function<void ()>& cb)
    {
        return resize_signal.connect(cb);
    }

    void Window::disconnect_resize(const rsig::connection& con)
    {
        return resize_signal.disconnect(con);
    }

    void Window::draw()
    {
        draw_signal.emit();

        SDL_GL_SwapWindow(window);
    }

    void Window::handle_events(const SDL_Event& ev)
    {
        if (ev.type == SDL_WINDOWEVENT && ev.window.windowID == SDL_GetWindowID(window))
        {
            switch (ev.window.event)
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    resize_signal.emit();
                    break;
            }
        }
    }

    void show_message_box(MessageBoxFlags flags, const std::string& title, const std::string& text)
    {
        auto r = SDL_ShowSimpleMessageBox(stdex::to_underlying(flags), title.data(), text.data(), nullptr);
        if (r < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    void show_message_box(Window& window, MessageBoxFlags flags, const std::string& title, const std::string& text)
    {
        auto r = SDL_ShowSimpleMessageBox(stdex::to_underlying(flags), title.data(), text.data(), window.window);
        if (r < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }
}

