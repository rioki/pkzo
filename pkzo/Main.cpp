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
#include "Main.h"

#include "async.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"
#include "Window.h"

namespace pkzo
{
    Main::Main()
    {
        async::set_main_thread_id(std::this_thread::get_id());

        mouse = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();

        auto jn = SDL_NumJoysticks();
        for (auto j = 0; j < jn; j++)
        {
            joysticks.push_back(std::make_unique<Joystick>(j));
        }
    }

    Main::~Main() = default;

    Mouse& Main::get_mouse() noexcept
    {
        assert(mouse);
        return *mouse;
    }

    const Mouse& Main::get_mouse() const noexcept
    {
        assert(mouse);
        return *mouse;
    }

    Keyboard& Main::get_keyboard() noexcept
    {
        assert(keyboard);
        return *keyboard;
    }

    const Keyboard& Main::get_keyboard() const noexcept
    {
        assert(keyboard);
        return *keyboard;
    }

    size_t Main::get_joystick_count() const noexcept
    {
        return joysticks.size();
    }

    Joystick& Main::get_joystick(size_t id) noexcept
    {
        assert(id < joysticks.size());
        assert(joysticks[id]);
        return *joysticks[id];
    }

    const Joystick& Main::get_joystick(size_t id) const noexcept
    {
        assert(id < joysticks.size());
        assert(joysticks[id]);
        return *joysticks[id];
    }

    Window& Main::open_window(const glm::uvec2& size, WindowMode mode, const std::string_view caption)
    {
        auto window = std::make_unique<Window>(size, mode, caption);
        auto tmp = window.get();
        windows.push_back(move(window));
        return *tmp;
    }

    Window& Main::get_main_window() noexcept
    {
        assert(!windows.empty());
        assert(windows.front());
        return *windows.front();
    }

    const Window& Main::get_main_window() const noexcept
    {
        assert(!windows.empty());
        assert(windows.front());
        return *windows.front();
    }

    void Main::run()
    {
        running = true;
        while (running)
        {
            tick();
        }
    }

    void Main::tick()
    {
        handle_events();
        if (tick_cb)
        {
            tick_cb();
        }
        for (const auto& window : windows)
        {
            window->draw();
        }
        async::sync_point();
    }

    void Main::stop()
    {
        running = false;
    }

    void Main::on_tick(const std::function<void()>& cb)
    {
        tick_cb = cb;
    }

    void Main::on_quit(const std::function<void()>&cb)
    {
        quit_cb = cb;
    }

    void Main::handle_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    if (quit_cb)
                    {
                        quit_cb();
                    }
                    else
                    {
                        stop();
                    }
                    break;
                }
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                    assert(mouse);
                    mouse->handle_event(event);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                    assert(keyboard);
                    keyboard->handle_event(event);
                    break;
                case SDL_JOYAXISMOTION:
                case SDL_JOYBALLMOTION:
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                case SDL_JOYHATMOTION:
                    for (const auto& joystick : joysticks)
                    {
                        assert(joystick);
                        joystick->handle_event(event);
                    }
                    break;
                case SDL_JOYDEVICEADDED:
                case SDL_JOYDEVICEREMOVED:
                    // TODO
                    break;
                case SDL_WINDOWEVENT:
                    for (const auto& window : windows)
                    {
                        assert(window);
                        window->handle_event(event);
                    }
                    break;
                default:
                    // do nothing
                    break;
            }
        }
    }
}
