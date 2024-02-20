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
#include "EventRouter.h"

#include "SdlInit.h"

namespace pkzo
{
    class EventRouter::EventRouterImpl
    {
    public:
        EventRouterImpl() noexcept = default;
        ~EventRouterImpl() = default;

        rex::signal<>& get_quit_signal()
        {
            return quit_signal;
        }

        void add_handler(InputHandler* handler)
        {
            assert(handler != nullptr);
            handlers.push_back(handler);
        }

        void remove_handler(InputHandler* handler)
        {
            assert(handler != nullptr);
            auto it = std::find(handlers.begin(), handlers.end(), handler);
            assert(it != handlers.end());
            handlers.erase(it);
        }

        // DESIGN: The types KeyMod, Key and MouseButton are specifically designed to match the SDL2 types.
        void route_events()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quit_signal.emit();
                    break;
                case SDL_KEYDOWN:
                    for (auto handler : handlers)
                    {
                        handler->handle_keboard_down(static_cast<KeyMod>(event.key.keysym.mod), static_cast<Key>(event.key.keysym.scancode));
                    }
                    break;
                case SDL_KEYUP:
                    for (auto handler : handlers)
                    {
                        handler->handle_keboard_up(static_cast<KeyMod>(event.key.keysym.mod), static_cast<Key>(event.key.keysym.scancode));
                    }
                    break;
                case SDL_TEXTINPUT:
                    for (auto handler : handlers)
                    {
                        handler->handle_keboard_text(event.text.text);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (auto handler : handlers)
                    {
                        handler->handle_mouse_button_down(static_cast<MouseButton>(event.button.button), { event.button.x, event.button.y });
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    for (auto handler : handlers)
                    {
                        handler->handle_mouse_button_up(static_cast<MouseButton>(event.button.button), { event.button.x, event.button.y });
                    }
                    break;
                case SDL_MOUSEMOTION:
                    for (auto handler : handlers)
                    {
                        handler->handle_mouse_move({ event.motion.x, event.motion.y }, { event.motion.xrel, event.motion.yrel });
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    for (auto handler : handlers)
                    {
                        handler->handle_mouse_wheel({ event.wheel.x, event.wheel.y });
                    }
                    break;
                default:
                    break;
                }
            }
        }

    private:
        SdlInit                    sdl_init;
        rex::signal<>              quit_signal;
        std::vector<InputHandler*> handlers;
    };

    EventRouter::EventRouter() noexcept
    : impl(std::make_unique<EventRouterImpl>()) {}

    EventRouter::~EventRouter() = default;

    rex::connection EventRouter::on_quit(const std::function<void()>& cb)
    {
        return impl->get_quit_signal().connect(cb);
    }

    rex::signal<>& EventRouter::get_quit_signal()
    {
        return impl->get_quit_signal();
    }

    void EventRouter::add_handler(InputHandler* handler)
    {
        impl->add_handler(handler);
    }

    void EventRouter::remove_handler(InputHandler* handler)
    {
        impl->remove_handler(handler);
    }

    void EventRouter::route_events()
    {
        impl->route_events();
    }
}
