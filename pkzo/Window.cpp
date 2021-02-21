//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Window.h"

namespace pkzo
{
    void clear_errors()
    {
        GLenum e;
        do
        {
            e = glGetError();
        }
        while (e != GL_NO_ERROR);
    }

    unsigned int Window::get_display_count() noexcept
    {
        return SDL_GetNumVideoDisplays();
    }

    std::vector<glm::uvec2> Window::get_valid_reslutions(unsigned int display) noexcept
    {
        std::vector<glm::uvec2> result;
        auto count = SDL_GetNumDisplayModes(display);
        for (auto i = 0; i < count; i++)
        {
            SDL_DisplayMode mode;
            SDL_GetDisplayMode(display, i, &mode);

            auto resolution = glm::uvec2(mode.w, mode.h);
            auto j = std::find(begin(result), end(result), resolution);
            if (j == end(result))
            {
                result.push_back(resolution);
            }
        }
        return result;
    }

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

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }
        clear_errors();
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
            if (mode == WindowMode::FULLSCREEN)
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
        if ((sdl_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
        {
            return WindowMode::FULLSCREEN;
        }
        else if ((sdl_flags & SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE)
        {
            return WindowMode::RESIZABLE;
        }
        else
        {
            return WindowMode::STATIC;
        }
    }

    void Window::close()
    {
        SDL_DestroyWindow(window);
    }

    void Window::on_draw(const std::function<void()>& cb)
    {
        draw_cb = cb;
    }

    void Window::on_show(const std::function<void()>& cb)
    {
        show_cb = cb;
    }

    void Window::on_hide(const std::function<void()>& cb)
    {
        hide_cb = cb;
    }

    void Window::on_exposed(const std::function<void()>& cb)
    {
        exposed_cb = cb;
    }

    void Window::on_moved(const std::function<void(glm::ivec2)>& cb)
    {
        moved_cb = cb;
    }

    void Window::on_resized(const std::function<void(glm::uvec2)>& cb)
    {
        resized_cb = cb;
    }

    void Window::on_size_changed(const std::function<void(glm::uvec2)>& cb)
    {
        size_changed_cb = cb;
    }

    void Window::on_minimixed(const std::function<void()>& cb)
    {
        minimize_cb = cb;
    }

    void Window::on_maximixed(const std::function<void()>& cb)
    {
        maximize_cb = cb;
    }

    void Window::on_restore(const std::function<void()>& cb)
    {
        restore_cb = cb;
    }

    void Window::on_enter(const std::function<void()>& cb)
    {
        enter_cb = cb;
    }

    void Window::on_leave(const std::function<void()>& cb)
    {
        leave_cb = cb;
    }

    void Window::on_gain_focus(const std::function<void()>& cb)
    {
        gain_focus_cb = cb;
    }

    void Window::on_lose_focus(const std::function<void()>& cb)
    {
        lose_focus_cb = cb;
    }

    void Window::on_close(const std::function<void()>& cb)
    {
        close_cb = cb;
    }


    void Window::draw() const noexcept
    {
        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        if (draw_cb)
        {
            draw_cb();
        }

        SDL_GL_SwapWindow(window);
    }

    void Window::handle_event(const SDL_Event& event) const
    {
        assert(event.type == SDL_WINDOWEVENT);
        if (SDL_GetWindowID(window) == event.window.windowID)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_SHOWN:
                if (show_cb)
                {
                    show_cb();
                }
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                if (hide_cb)
                {
                    show_cb();
                }
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                if (exposed_cb)
                {
                    show_cb();
                }
                break;
            case SDL_WINDOWEVENT_MOVED:
                if (moved_cb)
                {
                    moved_cb({event.window.data1, event.window.data2});
                }
                break;
            case SDL_WINDOWEVENT_RESIZED:
                if (resized_cb)
                {
                    resized_cb({event.window.data1, event.window.data2});
                }
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                if (size_changed_cb)
                {
                    size_changed_cb({event.window.data1, event.window.data2});
                }
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                if (minimize_cb)
                {
                    minimize_cb();
                }
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                if (maximize_cb)
                {
                    maximize_cb();
                }
                break;
            case SDL_WINDOWEVENT_RESTORED:
                if (restore_cb)
                {
                    restore_cb();
                }
                break;
            case SDL_WINDOWEVENT_ENTER:
                if (enter_cb)
                {
                    enter_cb();
                }
                break;
            case SDL_WINDOWEVENT_LEAVE:
                if (leave_cb)
                {
                    leave_cb();
                }
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                if (gain_focus_cb)
                {
                    gain_focus_cb();
                }
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                if (lose_focus_cb)
                {
                    lose_focus_cb();
                }
                break;
            case SDL_WINDOWEVENT_CLOSE:
                if (close_cb)
                {
                    close_cb();
                }
                break;
            case SDL_WINDOWEVENT_TAKE_FOCUS:
            case SDL_WINDOWEVENT_HIT_TEST:
            default:
                // meh...
                break;
            }
        }
        else
        {
            assert(false);
        }
    }
}