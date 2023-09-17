// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include <GL/glew.h>

#include "EventRouter.h"
#include "Texture.h"

namespace pkzo
{

    Window::Window(const glm::uvec2& size, const std::string_view caption)
    : Window(nullptr, size, SDL_WINDOW_RESIZABLE, caption) {}

    Window::Window(Fullscreen, const std::string_view caption)
    : Window(nullptr, {0,0}, SDL_WINDOW_FULLSCREEN_DESKTOP, caption) {}

    Window::Window(EventRouter& _router, const glm::uvec2& size, const std::string_view caption)
    : Window(&_router, size, SDL_WINDOW_RESIZABLE, caption) {}

    Window::Window(EventRouter& _router, Fullscreen, const std::string_view caption)
    : Window(&_router, {0,0}, SDL_WINDOW_FULLSCREEN_DESKTOP, caption) {}

    Window::~Window()
    {
        if (router)
        {
            router->get_event_signal().disconnect(router_connection);
        }
    }

    glm::uvec2 Window::get_size() const noexcept
    {
        int w = 0;
        int h = 0;
        SDL_GetWindowSize(window, &w, &h);
        return {w, h};
    }

    glm::uvec2 Window::get_drawable_size() const noexcept
    {
        int w = 0;
        int h = 0;
        SDL_GL_GetDrawableSize(window, &w, &h);
        return {w, h};
    }

    bool Window::is_fullscreen() const noexcept
    {
        return (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN;
    }

    void Window::make_fullscreen()
    {
        if (! is_fullscreen())
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }

    void Window::make_windowed(const glm::uvec2& size)
    {
        if (is_fullscreen())
        {
            SDL_SetWindowFullscreen(window, SDL_FALSE);
        }

        SDL_SetWindowSize(window, size.x, size.y);
    }

    std::string Window::get_caption() const noexcept
    {
        auto text = SDL_GetWindowTitle(window);
        if (text == nullptr)
        {
            return {};
        }

        return text;
    }

    void Window::set_caption(const std::string_view value)
    {
        SDL_SetWindowTitle(window, value.data());
    }

    rsig::signal<>& Window::get_draw_signal() noexcept
    {
        return draw_signal;
    }

    rsig::signal<glm::uvec2>& Window::get_resize_signal() noexcept
    {
        return resize_signal;
    }

    void Window::draw()
    {
        auto size = get_drawable_size();

        glViewport(0, 0, size.x, size.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_signal.emit();

        SDL_GL_SwapWindow(window);
    }

    std::shared_ptr<Texture> Window::save_screen() const
    {
        auto size = get_drawable_size();
        std::vector<uint8_t> buffer(size.x * size.y * 3);
        glReadPixels(0, 0, size.x, size.y, GL_BGR, GL_UNSIGNED_BYTE, buffer.data());
        return Texture::create_from_buffer(size, ColorMode::RGB, DataType::UINT8, buffer.data(), "screen");
    }

    Window::Window(EventRouter* _router, const glm::uvec2& size, unsigned int flags, const std::string_view caption)
    {
        window = SDL_CreateWindow(caption.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL | flags);
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

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }

        if (_router)
        {
            router = _router;
            router_connection = router->get_event_signal().connect(rsig::mem_fun(this, &Window::handle_events));
        }
    }

    void Window::handle_events(const SDL_Event& event)
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.windowID == SDL_GetWindowID(window))
            {
                switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                        {
                            int width  = event.window.data1;
                            int height = event.window.data2;
                            resize_signal.emit({width, height});
                            break;
                        }
                        default:
                            // STFU
                            break;
                    }
            }
        }
    }
}
