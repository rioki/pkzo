// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Window.h"

#include <SDL3/SDL.h>

#include <tinyformat.h>

namespace pkzo
{
    std::vector<Window*> Window::instances;

    void Window::route_event(const SDL_Event& event)
    {
        // TODO
    }

    Window::Window(Init init)
    {
        instances.push_back(this);

        auto flags = std::to_underlying(init.api)
                   | std::to_underlying(init.state);
        window = SDL_CreateWindow(init.title.data(), init.size.x, init.size.y, flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        graphic_context = GraphicContext::create(init.api, window);
    }

    Window::~Window()
    {
        graphic_context = nullptr;
        SDL_DestroyWindow(window);

        std::erase(instances, this);
    }

    glm::uvec2 Window::get_size() const
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
    }

    void Window::set_size(const glm::uvec2& value)
    {
        SDL_SetWindowSize(window, value.x, value.y);
    }

    glm::uvec2 Window::get_resolution() const
    {
        int w, h;
        SDL_GetWindowSizeInPixels(window, &w, &h);
        return {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
    }

    WindowState Window::get_state() const
    {
        auto flags = SDL_GetWindowFlags(window);
        if (flags & SDL_WINDOW_FULLSCREEN)
        {
            return WindowState::FULLSCREEN;
        }
        else if (flags & SDL_WINDOW_MINIMIZED)
        {
            return WindowState::MINIMIZED;
        }
        else if (flags & SDL_WINDOW_MAXIMIZED)
        {
            return WindowState::MAXIMIZED;
        }
        else
        {
            return WindowState::WINDOW;
        }
    }

    bool Window::get_fullscreen() const
    {
        return get_state() == WindowState::FULLSCREEN;
    }

    void Window::set_fullscreen(bool value)
    {
        SDL_SetWindowFullscreen(window, value);
    }

    void Window::capture_mouse()
    {
        SDL_SetWindowRelativeMouseMode(window, true);
    }

    void Window::release_mouse()
    {
        SDL_SetWindowRelativeMouseMode(window, false);
    }

    rsig::connection Window::on_draw(const std::function<void (GraphicContext&)>& handler)
    {
        return draw_signal.connect(handler);
    }

    void Window::draw()
    {
        graphic_context->set_viewport({
            .size = get_resolution()
        });
        graphic_context->clear_screen();

        draw_signal.emit(*graphic_context);

        graphic_context->swap_buffers();
    }
}
