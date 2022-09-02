// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <cassert>
#include <atomic>
#include <memory>
#include <filesystem>
#include <vector>

#include "Settings.h"

namespace ice
{
    class System;
    class Window;
    class Mouse;
    class Keyboard;
    class Joystick;
    class Screen;

    class ICE_EXPORT Engine
    {
    public:
        Engine();

        ~Engine();

        [[nodiscard]]
        Settings& get_settings() noexcept;

        [[nodiscard]]
        const Settings& get_settings() const noexcept;

        void load_settings(const std::filesystem::path& file);

        void save_settings(const std::filesystem::path& file);

        [[nodiscard]]
        Window* get_window() noexcept;
        [[nodiscard]]
        const Window* get_window() const noexcept;

        [[nodiscard]]
        Mouse* get_mouse() noexcept;
        [[nodiscard]]
        const Mouse* get_mouse() const noexcept;

        [[nodiscard]]
        Keyboard* get_keyboard() noexcept;
        [[nodiscard]]
        const Keyboard* get_keyboard() const noexcept;

        [[nodiscard]]
        std::vector<Joystick*> get_joysticks() noexcept;
        [[nodiscard]]
        std::vector<const Joystick*> get_joysticks() const noexcept;

        template <typename SystemT>
        void start_system();

        template <typename SystemT> [[nodiscard]]
        SystemT* get_system();

        template <typename SystemT> [[nodiscard]]
        const SystemT* get_system() const;

        void set_overlay(const std::shared_ptr<Screen>& value) noexcept;
        const std::shared_ptr<Screen>& get_overlay() const noexcept;

        void tick();
        void run();
        void stop();

    private:
        std::atomic<bool>                    running = false;
        Settings                             settings;
        std::vector<std::unique_ptr<System>> systems;
        std::shared_ptr<Screen>              overlay;

        Engine(const Engine&) = delete;
        Engine& operator = (const Engine&) = delete;
    };

    template <typename SystemT>
    void Engine::start_system()
    {
        assert(running == false);
        assert(get_system<SystemT>() == nullptr);
        systems.push_back(std::make_unique<SystemT>(*this));
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
