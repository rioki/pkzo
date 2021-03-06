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

#include "glmio.h"
#include "sync.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"
#include "Window.h"
#include "Settings.h"

namespace pkzo
{
    Main::Main() noexcept
    {
        sync::set_main_thread_id(std::this_thread::get_id());

        mouse = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();

        auto jn = SDL_NumJoysticks();
        for (auto j = 0; j < jn; j++)
        {
            joysticks.push_back(std::make_unique<Joystick>(j));
        }

        last_tick = std::chrono::steady_clock::now();
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
        return get_window(0);
    }

    const Window& Main::get_main_window() const noexcept
    {
        return get_window(0);
    }

    size_t Main::get_open_windows() const noexcept
    {
        return windows.size();
    }

    Window& Main::get_window(size_t index) noexcept
    {
        DBG_ASSERT(index < windows.size());
        return *windows[index];
    }

    const Window& Main::get_window(size_t index) const noexcept
    {
        DBG_ASSERT(index < windows.size());
        return *windows[index];
    }

    void Main::run()
    {
        running = true;
        last_tick = std::chrono::steady_clock::now();
        while (running)
        {
            tick();
        }
    }

    void Main::tick()
    {
        auto now = std::chrono::steady_clock::now();
        auto dt  = now - last_tick;
        last_tick = now;

        handle_events();
        tick_signal.emit(std::chrono::duration_cast<std::chrono::milliseconds>(dt));
        for (const auto& window : windows)
        {
            window->draw();
        }
        sync::sync_point();
    }

    void Main::stop()
    {
        running = false;
    }

    rsig::signal<std::chrono::milliseconds>& Main::get_tick_signal() noexcept
    {
        return tick_signal;
    }

    rsig::connection Main::on_tick(const std::function<void(std::chrono::milliseconds)>& cb) noexcept
    {
        return tick_signal.connect(cb);
    }

    rsig::signal<>& Main::get_quit_signal() noexcept
    {
        return quit_signal;
    }

    rsig::connection Main::on_quit(const std::function<void()>& cb) noexcept
    {
        return quit_signal.connect(cb);
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
                    if (quit_signal.emit() == 0)
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
