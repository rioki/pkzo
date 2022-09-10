// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "Window.h"

#include "utils.h"

namespace ice
{
    Window::Window(const glm::uvec2& size, WindowMode mode, const std::string_view caption)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        Uint32 sdl_flags = SDL_WINDOW_OPENGL;
        switch (mode)
        {
            case WindowMode::FULLSCREEN:
                sdl_flags |= SDL_WINDOW_FULLSCREEN;
                break;
            case WindowMode::NATIVE_FULLSCREEN:
                sdl_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
                break;
            case WindowMode::RESIZABLE:
                sdl_flags |= SDL_WINDOW_RESIZABLE;
                break;
        }

        window = SDL_CreateWindow(caption.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, sdl_flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
        #ifndef NDEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        #endif

        glow::init();
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(glcontext);
        SDL_DestroyWindow(window);
    }

    void Window::set_caption(const std::string_view text) noexcept
    {
        SDL_SetWindowTitle(window, text.data());
    }

    std::string Window::get_caption() const noexcept
    {
        auto caption = SDL_GetWindowTitle(window);
        if (caption != nullptr)
        {
            return {caption};
        }
        else
        {
            return {};
        }
    }

    void Window::resize(const glm::uvec2& size, WindowMode mode)
    {
        auto old_mode = get_mode();
        if (mode == old_mode)
        {
            SDL_SetWindowSize(window, size.x, size.y);
        }
        else
        {
            // prevent an unnecessary resolution switch on the monitor.
            if (mode == WindowMode::FULLSCREEN || mode == WindowMode::NATIVE_FULLSCREEN)
            {
                SDL_SetWindowSize(window, size.x, size.y);
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            }

            if (old_mode == WindowMode::FULLSCREEN)
            {
                SDL_SetWindowFullscreen(window, 0);
                SDL_SetWindowSize(window, size.x, size.y);
            }

            SDL_SetWindowResizable(window, (mode == WindowMode::RESIZABLE) ? SDL_TRUE : SDL_FALSE);
        }
    }

    glm::uvec2 Window::get_size() const noexcept
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return {w, h};
    }

    WindowMode Window::get_mode() const noexcept
    {
        auto sdl_flags = SDL_GetWindowFlags(window);
        if ((sdl_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP)
        {
            return WindowMode::RESIZABLE;
        }
        if ((sdl_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
        {
            return WindowMode::FULLSCREEN;
        }
        if ((sdl_flags & SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE)
        {
            return WindowMode::RESIZABLE;
        }
        return WindowMode::STATIC;
    }

    rsig::signal<>& Window::get_draw_sginal() noexcept
    {
        return draw_signal;
    }

    rsig::connection Window::on_draw(const std::function<void()>& cb) noexcept
    {
        return draw_signal.connect(cb);
    }

    void Window::draw() const noexcept
    {
        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        draw_signal.emit();
        SDL_GL_SwapWindow(window);
    }
}