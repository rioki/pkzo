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
#include "Engine.h"

#include "System.h"
#include "GraphicSystem.h"
#include "InputSystem.h"
#include "Screen.h"

namespace ice
{
    Engine::Engine()
    {
        c9y::set_main_thread_id(std::this_thread::get_id());
    }

    Engine::~Engine()
    {
        if (overlay)
        {
            overlay->deactivate(*this);
            overlay = nullptr;
        }

        // destruct in reverse order
        while (!systems.empty())
        {
            systems.erase(begin(systems) + (systems.size() - 1));
        }
    }

    Settings& Engine::get_settings() noexcept
    {
        return settings;
    }

    const Settings& Engine::get_settings() const noexcept
    {
        return settings;
    }

    void Engine::load_settings(const std::filesystem::path& file)
    {
        settings.load(file);
    }

    void Engine::save_settings(const std::filesystem::path& file)
    {
        settings.save(file);
    }

    std::string Engine::get_setting(const std::string& section, const std::string& key, const std::string& initial) const noexcept
    {
        return settings.get_value(section, key, initial);
    }

    AssetLibrary& Engine::get_asset_library() noexcept
    {
        return asset_library;
    }

    const AssetLibrary& Engine::get_asset_library() const noexcept
    {
        return asset_library;
    }

    void Engine::add_asset_folder(const std::filesystem::path& dir) noexcept
    {
        asset_library.add_directory(dir);
    }

    Window* Engine::get_window() noexcept
    {
        auto gs = get_system<GraphicSystem>();
        if (nullptr == gs)
        {
            return nullptr;
        }
        return gs->get_window();
    }

    const Window* Engine::get_window() const noexcept
    {
        auto gs = get_system<GraphicSystem>();
        if (nullptr == gs)
        {
            return nullptr;
        }
        return gs->get_window();
    }

    Mouse* Engine::get_mouse() noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return nullptr;
        }
        return is->get_mouse();
    }

    const Mouse* Engine::get_mouse() const noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return nullptr;
        }
        return is->get_mouse();
    }

    Keyboard* Engine::get_keyboard() noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return nullptr;
        }
        return is->get_keyboard();
    }

    const Keyboard* Engine::get_keyboard() const noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return nullptr;
        }
        return is->get_keyboard();
    }

    std::vector<Joystick*> Engine::get_joysticks() noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return {};
        }
        return is->get_joysticks();
    }

    std::vector<const Joystick*> Engine::get_joysticks() const noexcept
    {
        auto is = get_system<InputSystem>();
        if (nullptr == is)
        {
            return {};
        }
        return is->get_joysticks();
    }

    void Engine::set_overlay(const std::shared_ptr<Screen>& value) noexcept
    {
        c9y::delay([this, value] () {
            if (overlay)
            {
                overlay->deactivate(*this);
            }
            overlay = value;
            if (overlay)
            {
                overlay->activate(*this);
            }
        });
    }

    const std::shared_ptr<Screen>& Engine::get_overlay() const noexcept
    {
        return overlay;
    }

    rsig::connection Engine::on_tick(const std::function<void ()>& cb) noexcept
    {
        return tick_signal.connect(cb);
    }

    rsig::signal<>& Engine::get_tick_signal() noexcept
    {
        return tick_signal;
    }

    void Engine::activate()
    {
        for (const auto& system : systems)
        {
            system->activate();
        }
    }

    void Engine::tick()
    {
        c9y::sync_point();

        for (const auto& sys : systems)
        {
            sys->tick();
            tick_signal.emit();
        }
    }



    void Engine::deactivate()
    {
        for (const auto& system : std::views::reverse(systems))
        {
            system->deactivate();
        }
    }

    void Engine::run()
    {
        running = true;
        activate();

        while (running)
        {
            tick();
        }

        deactivate();
    }

    void Engine::stop()
    {
        running = false;
    }


}
