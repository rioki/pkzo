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
#include "Engine.h"

#include "glmio.h"
#include "sync.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"
#include "Window.h"
#include "Settings.h"

namespace pkzo
{
    Engine::Engine(const std::string& i)
    : id(i)
    {
        sync::set_main_thread_id(std::this_thread::get_id());

        settings = std::make_unique<Settings>();
        auto settings_file = get_user_folder() / "settings.json";
        if (std::filesystem::exists(settings_file))
        {
            settings->load(settings_file);
        }

        // TODO in release the defaults should be fullscreen & native resolution
        auto resolution = settings->get_value("Graphic", "resolution", glm::uvec2(800, 600));
        auto fullscreen = settings->get_value("Graphic", "fullscreen", false);
        open_window(resolution, fullscreen ? WindowMode::FULLSCREEN : WindowMode::STATIC, id);

        mouse = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();

        auto jn = SDL_NumJoysticks();
        for (auto j = 0; j < jn; j++)
        {
            joysticks.push_back(std::make_unique<Joystick>(j));
        }

        last_tick = std::chrono::steady_clock::now();
    }

    Engine::~Engine()
    {
        try
        {
            settings->save(get_user_folder() / "settings.json");
        }
        catch (const std::exception& ex)
        {
            DBG_FAIL(ex.what());
        }
    }

    const std::string& Engine::get_id() const noexcept
    {
        return id;
    }

    std::filesystem::path Engine::get_user_folder() const
    {
        std::scoped_lock sl(mutex);
        if (user_folder.empty())
        {
            #ifdef _WIN32
            PWSTR path = nullptr;
            auto hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &path);
            if (SUCCEEDED(hr))
            {
                user_folder = std::filesystem::path(path) / id;
                CoTaskMemFree(path);
                if (!std::filesystem::exists(user_folder))
                {
                    std::filesystem::create_directories(user_folder);
                }
                return user_folder;
            }
            else
            {
                throw std::runtime_error("Failed to get %LOCALAPPDATA%.");
            }
            #else
            #error port me
            #endif
        }
        else
        {
            return user_folder;
        }
    }

    std::filesystem::path Engine::get_temp_folder() const
    {
        std::scoped_lock sl(mutex);
        if (temp_folder.empty())
        {
            #ifdef _WIN32
            TCHAR path[MAX_PATH];
            auto ret = GetTempPath(MAX_PATH, path); // buffer for path
            if (ret > MAX_PATH || (ret == 0))
            {
                throw std::runtime_error("Failed to get temporary folder.");
            }
            else
            {
                temp_folder = std::filesystem::path(path) / id;
                if (!std::filesystem::exists(temp_folder))
                {
                    std::filesystem::create_directories(temp_folder);
                }
                return temp_folder;
            }
            #else
            #error port me
            #endif
        }
        else
        {
            return temp_folder;
        }
    }

    Settings& Engine::get_settings() noexcept
    {
        DBG_ASSERT(settings);
        return *settings;
    }

    const Settings& Engine::get_settings() const noexcept
    {
        DBG_ASSERT(settings);
        return *settings;
    }

    Mouse& Engine::get_mouse() noexcept
    {
        assert(mouse);
        return *mouse;
    }

    const Mouse& Engine::get_mouse() const noexcept
    {
        assert(mouse);
        return *mouse;
    }

    Keyboard& Engine::get_keyboard() noexcept
    {
        assert(keyboard);
        return *keyboard;
    }

    const Keyboard& Engine::get_keyboard() const noexcept
    {
        assert(keyboard);
        return *keyboard;
    }

    size_t Engine::get_joystick_count() const noexcept
    {
        return joysticks.size();
    }

    Joystick& Engine::get_joystick(size_t id) noexcept
    {
        assert(id < joysticks.size());
        assert(joysticks[id]);
        return *joysticks[id];
    }

    const Joystick& Engine::get_joystick(size_t id) const noexcept
    {
        assert(id < joysticks.size());
        assert(joysticks[id]);
        return *joysticks[id];
    }

    Window& Engine::open_window(const glm::uvec2& size, WindowMode mode, const std::string_view caption)
    {
        auto window = std::make_unique<Window>(size, mode, caption);
        auto tmp = window.get();
        windows.push_back(move(window));
        return *tmp;
    }

    Window& Engine::get_main_window() noexcept
    {
        assert(!windows.empty());
        assert(windows.front());
        return *windows.front();
    }

    const Window& Engine::get_main_window() const noexcept
    {
        assert(!windows.empty());
        assert(windows.front());
        return *windows.front();
    }

    void Engine::run()
    {
        running = true;
        last_tick = std::chrono::steady_clock::now();
        while (running)
        {
            tick();
        }
    }

    void Engine::tick()
    {
        auto now = std::chrono::steady_clock::now();
        auto dt  = now - last_tick;
        last_tick = now;

        handle_events();
        if (tick_cb)
        {
            tick_cb(std::chrono::duration_cast<std::chrono::milliseconds>(dt));
        }
        for (const auto& window : windows)
        {
            window->draw();
        }
        sync::sync_point();
    }

    void Engine::stop()
    {
        running = false;
    }

    void Engine::on_tick(const std::function<void(std::chrono::milliseconds)>& cb)
    {
        tick_cb = cb;
    }

    void Engine::on_quit(const std::function<void()>&cb)
    {
        quit_cb = cb;
    }

    void Engine::handle_events()
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
