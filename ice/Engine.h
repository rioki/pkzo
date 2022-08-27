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

        template <typename SystemT>
        void start_system();

        template <typename SystemT>
        SystemT* get_system();

        template <typename SystemT>
        const SystemT* get_system() const;

        void tick();
        void run();
        void stop();

    private:
        std::atomic<bool>                    running = false;
        Settings                             settings;
        std::vector<std::unique_ptr<System>> systems;

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
            return s;
        }
        return nullptr;
    }

    template <typename SystemT>
    const SystemT* Engine::get_system() const
    {
        return const_cast<Engine*>(this)->get_system();
    }
}
