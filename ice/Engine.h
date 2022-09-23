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

#pragma once
#include "config.h"

#include <cassert>
#include <atomic>
#include <memory>
#include <filesystem>
#include <vector>
#include <type_traits>

#include <rsig/rsig.h>

#include "Settings.h"
#include "AssetLibrary.h"

namespace ice
{
    class System;
    class Window;
    class Mouse;
    class Keyboard;
    class Joystick;
    class Screen;
    class Scene;

    class ICE_EXPORT Engine
    {
    public:
        Engine();

        ~Engine();


        Settings& get_settings() noexcept;
        const Settings& get_settings() const noexcept;
        void load_settings(const std::filesystem::path& file);
        void save_settings(const std::filesystem::path& file);
        template <typename Type>
        Type get_setting(const std::string& section, const std::string& key, const Type& initial) const noexcept;
        std::string get_setting(const std::string& section, const std::string& key, const std::string& initial) const noexcept;

        AssetLibrary& get_asset_library() noexcept;
        const AssetLibrary& get_asset_library() const noexcept;

        void add_asset_folder(const std::filesystem::path& dir) noexcept;

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load_asset(const Args& ... args);

        Window* get_window() noexcept;
        const Window* get_window() const noexcept;

        Mouse* get_mouse() noexcept;
        const Mouse* get_mouse() const noexcept;

        Keyboard* get_keyboard() noexcept;
        const Keyboard* get_keyboard() const noexcept;

        std::vector<Joystick*> get_joysticks() noexcept;
        std::vector<const Joystick*> get_joysticks() const noexcept;

        template <typename SystemT>
        SystemT* start_system();

        template <typename SystemT>
        SystemT* get_system();

        template <typename SystemT>
        const SystemT* get_system() const;

        void set_scene(const std::shared_ptr<Scene>& value) noexcept;
        const std::shared_ptr<Scene>& get_scene() const noexcept;

        void set_overlay(const std::shared_ptr<Screen>& value) noexcept;
        const std::shared_ptr<Screen>& get_overlay() const noexcept;

        rsig::connection on_tick(const std::function<void ()>& cb) noexcept;
        rsig::signal<>& get_tick_signal() noexcept;

        void tick();
        void activate();
        void deactivate();
        void run(std::optional<unsigned int> max_tick_count = std::nullopt);
        void stop();

    private:
        std::atomic<bool>                    running    = false;
        unsigned int                         tick_count = 0u;
        rsig::signal<>                       tick_signal;
        Settings                             settings;
        AssetLibrary                         asset_library;
        std::vector<std::unique_ptr<System>> systems;
        std::shared_ptr<Scene>               scene;
        std::shared_ptr<Screen>              overlay;

        Engine(const Engine&) = delete;
        Engine& operator = (const Engine&) = delete;
    };

    template <typename Type>
    Type Engine::get_setting(const std::string& section, const std::string& key, const Type& initial) const noexcept
    {
        return settings.get_value(section, key, initial);
    }

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> Engine::load_asset(const Args& ... args)
    {
        return asset_library.load<AssetT>(args...);
    }

    template <typename SystemT>
    SystemT* Engine::start_system()
    {
        assert(running == false);
        assert(get_system<SystemT>() == nullptr);
        auto sys = std::make_unique<SystemT>(*this);
        auto ptr = sys.get();
        systems.emplace_back(std::move(sys));
        return ptr;
    }

    template <typename SystemT>
    SystemT* Engine::get_system()
    {
        for (const auto& sys : systems)
        {
            auto s = dynamic_cast<SystemT*>(sys.get());
            if (s != nullptr)
            {
                return s;
            }
        }
        return nullptr;
    }

    template <typename SystemT>
    const SystemT* Engine::get_system() const
    {
        return const_cast<Engine*>(this)->get_system<SystemT>();
    }
}
