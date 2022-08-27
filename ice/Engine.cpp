// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Engine.h"

#include "System.h"

namespace ice
{
    Engine::Engine() {}

    Engine::~Engine() {}

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

    void Engine::tick()
    {
        for (const auto& sys : systems)
        {
            sys->tick();
        }
    }

    void Engine::run()
    {
        running = true;
        while (running)
        {
            tick();
        }
    }

    void Engine::stop()
    {
        running = false;
    }
}
