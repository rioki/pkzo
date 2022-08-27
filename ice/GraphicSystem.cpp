// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "GraphicSystem.h"

#include "utils.h"
#include "Engine.h"
#include "Settings.h"
#include "Window.h"
#include "glm_json.h"

namespace ice
{
    GraphicSystem::GraphicSystem(Engine& e)
    : System(e)
    {
        const auto& settings = engine.get_settings();

        auto resolution = settings.get_value("GraphicSystem", "resolution", glm::vec2(800, 600));
        #if DEBUG
        auto mode = settings.get_value("GraphicSystem", "mode", WindowMode::STATIC);
        #else
        auto mode = settings.get_value("GraphicSystem", "mode", WindowMode::NATIVE_FULLSCREEN);
        #endif

        window = std::make_unique<Window>(resolution, mode, "Ice Engine");
        window->on_draw(rsig::mem_fun(this, &GraphicSystem::render_frame));
    }

    GraphicSystem::~GraphicSystem()
    {
        window = nullptr;
    }

    Window* GraphicSystem::get_window() noexcept
    {
        assert(window);
        return window.get();
    }

    const Window* GraphicSystem::get_window() const noexcept
    {
        assert(window);
        return window.get();
    }

    void GraphicSystem::tick()
    {
        assert(window);
        window->draw();
    }

    void GraphicSystem::render_frame() noexcept
    {

    }
}
