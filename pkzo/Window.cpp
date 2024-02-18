

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
#include "Window.h"

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, WindowMode mode)
    {
        switch (mode)
        {
            case WindowMode::WINDOWED:
                os << "WINDOWED";
                break;
            case WindowMode::FULLSCREEN:
                os << "FULLSCREEN";
                break;
            case WindowMode::FULLSCREEN_DESKTOP:
                os << "FULLSCREEN_DESKTOP";
                break;
            default:
                os << "WindowMode(0x" << std::hex << static_cast<unsigned int>(mode) << ")";
        }
        return os;
    }

    Uint32 get_sdl_window_flags(WindowMode mode)
    {
        switch (mode)
        {
            case WindowMode::WINDOWED:
                return SDL_WINDOW_RESIZABLE;
            case WindowMode::FULLSCREEN:
                return  SDL_WINDOW_FULLSCREEN;
            case WindowMode::FULLSCREEN_DESKTOP:
                return SDL_WINDOW_FULLSCREEN_DESKTOP;
            default:
                fail();
        }
    }

    Window::Window(EventRouter& er, const std::string_view& title, glm::uvec2 size, WindowMode mode)
    : Window(er, title, {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}, size, mode) {}

    Window::Window(EventRouter& er, const std::string_view& title, glm::ivec2 position, glm::uvec2 size, WindowMode mode)
    : event_router(er)
    {
        event_conn = event_router.on_event(rex::mem_fun(this, &Window::handle_event));

        auto flags = get_sdl_window_flags(mode) | SDL_WINDOW_OPENGL;
        window = SDL_CreateWindow(title.data(), position.x, position.y, size.x, size.y, flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        glow::init();
    }

    Window::~Window()
    {
        check(window != nullptr);
        SDL_GL_DeleteContext(glcontext);
        SDL_DestroyWindow(window);

        event_router.get_event_signal().disconnect(event_conn);
    }

    std::string_view Window::get_title() const noexcept
    {
        check(window != nullptr);
        auto result = SDL_GetWindowTitle(window);
        if (result == nullptr)
        {
            return "";
        }
        else
        {
            return result;
        }
    }

    glm::uvec2 Window::get_size() const noexcept
    {
        check(window != nullptr);
        int x, y;
        SDL_GetWindowSize(window, &x, &y);
        return {x, y};
    }

    glm::uvec2 Window::get_drawable_size() const noexcept
    {
        check(window != nullptr);
        int x, y;
        SDL_GL_GetDrawableSize(window, &x, &y);
        return {x, y};
    }

    WindowMode Window::get_window_mode() const noexcept
    {
        check(window != nullptr);
        auto flags = SDL_GetWindowFlags(window);

        if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
        {
            return WindowMode::FULLSCREEN_DESKTOP;
        }
        else if (flags & SDL_WINDOW_FULLSCREEN)
        {
            return WindowMode::FULLSCREEN;
        }
        else
        {
            return WindowMode::WINDOWED;
        }
    }

    glm::ivec2 Window::get_position() const noexcept
    {
        check(window != nullptr);
        int x, y;
        SDL_GetWindowPosition(window, &x, &y);
        return {x, y};
    }

    void Window::set_video_mode(glm::uvec2 size, WindowMode mode)
    {
        check(window != nullptr);
        auto flags = get_sdl_window_flags(mode);
        SDL_SetWindowSize(window, size.x, size.y);
        SDL_SetWindowFullscreen(window, flags);
    }

    void Window::set_position(glm::ivec2 position)
    {
        check(window != nullptr);
        SDL_SetWindowPosition(window, position.x, position.y);
    }

    void Window::init(const std::function<void()>& cb)
    {
        check(cb);
        check(window != nullptr);
        SDL_GL_MakeCurrent(window, glcontext);
        cb();
    }

    void Window::on_draw(const std::function<void()>& cb)
    {
        draw_cb = cb;
    }

    void Window::draw()
    {
        check(window != nullptr);
        SDL_GL_MakeCurrent(window, glcontext);

        auto size = get_drawable_size();
        glViewport(0, 0, size.x, size.y);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (draw_cb)
        {
            draw_cb();
        }

        SDL_GL_SwapWindow(window);
    }

    Image Window::get_screenshot() const
    {
        check(window != nullptr);
        SDL_GL_MakeCurrent(window, glcontext);

        auto size = get_size();
        auto pixels = std::vector<uint8_t>(size.x * size.y * 3);

        glReadPixels(0, 0, size.x, size.y, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());

        return Image(size, ColorMode::BGR, pixels.data());
    }

    void Window::handle_event(const SDL_Event& event)
    {
        // TODO #186838931
    }
}
