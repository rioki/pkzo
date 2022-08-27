// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Engine.h"

#include "System.h"
#include "GraphicSystem.h"
#include "InputSystem.h"

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
