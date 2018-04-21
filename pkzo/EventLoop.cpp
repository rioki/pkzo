// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "EventLoop.h"

#include <SDL.h>

namespace pkzo
{
    std::shared_ptr<Window> EventLoop::open_window(rgm::uvec2 sizet, bool fullscreen)
    {
        if (window)
        {
            throw std::logic_error(__FUNCTION__ ": Window is alread created.");
        }

        Window::Mode wm = fullscreen ? Window::FULLSCREEN : Window::RESIZABLE;
        window = std::make_shared<Window>(rgm::ivec2(sizet), wm);
        return window;
    }

    std::shared_ptr<Window> EventLoop::get_window()
    {
        if (!window)
        {
            throw std::logic_error(__FUNCTION__ ": No open window.");
        }
        return window;
    }

    std::shared_ptr<Mouse> EventLoop::get_mouse()
    {
        if (!mouse)
        {
            mouse = std::make_shared<Mouse>();
        }
        return mouse;
    }

    std::shared_ptr<Keyboard> EventLoop::get_keyboard()
    {
        if (!keyboard)
        {
            keyboard = std::make_shared<Keyboard>();
        }
        return keyboard;
    }

    void EventLoop::tick()
    {
        route_events();

        if (tick_cb)
        {
            tick_cb();
        }

        if (window)
        {
            window->draw();
        }
    }

    void EventLoop::run()
    {
        running = true;
        while (running)
        {
            tick();
        }
    }

    void EventLoop::stop()
    {
        running = false;
    }

    void EventLoop::on_tick(std::function<void ()> cb)
    {
        tick_cb = cb;
    }

    void EventLoop::route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                case SDL_WINDOWEVENT:
                // TODO other window events
                {
                    bool handled = false;
                    if (window)
                    {
                        handled = window->handle_event(event);
                    }

                    // Special handling for the case where no close handler
                    // is installed on the window.
                    if (!handled && event.type == SDL_QUIT)
                    {
                        stop();
                    }
                    break;
                }
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    if (keyboard)
                    {
                        keyboard->handle_event(event);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    if (mouse)
                    {
                        mouse->handle_event(event);
                    }
                    break;
                default:
                    /* stfu */
                    break;
            }
        }
    }
}
