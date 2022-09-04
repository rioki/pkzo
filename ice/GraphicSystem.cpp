// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "GraphicSystem.h"

#include "utils.h"
#include "Engine.h"
#include "Settings.h"
#include "Window.h"
#include "Texture.h"
#include "glm_json.h"
#include "Screen.h"
#include "ScreenRenderer.h"

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

    const glm::uvec2 GraphicSystem::get_window_size() const noexcept
    {
        if (window)
        {
            return window->get_size();
        }
        else
        {
            return glm::uvec2(0u);
        }
    }

    ScreenRenderer* GraphicSystem::create_screen_renderer() noexcept
    {
        return add_unique_ptr<ScreenRenderer>(screen_renderers);
    }

    void GraphicSystem::release_screen_renderer(ScreenRenderer* renderer) noexcept
    {
        remove_unique_ptr(screen_renderers, renderer);
    }

    void GraphicSystem::tick()
    {
        assert(window);
        window->draw();
    }

    std::shared_ptr<Texture> GraphicSystem::get_screenshot() const noexcept
    {
        auto s = window->get_size();
        std::vector<std::byte> buffer(s.x * s.y * 3);
        glReadPixels(0, 0, s.x, s.y, GL_BGR, GL_UNSIGNED_BYTE, buffer.data());
        return std::make_shared<Texture>(s, ColorMode::RGB, DataType::UINT8, buffer.data(), "screen");
    }

    rsig::connection GraphicSystem::debug_draw(const std::function<void ()>& cb) noexcept
    {
        return debug_draw_signal.connect(cb);
    }

    rsig::signal<>& GraphicSystem::get_debug_draw_signal() noexcept
    {
        return debug_draw_signal;
    }

    void GraphicSystem::render_frame() noexcept
    {
        // 3D Scene

        // 2D Overlay / HUD
        const auto& overlay = engine.get_overlay();
        if (overlay)
        {
            overlay->draw();
        }

        // Debug
        debug_draw_signal.emit();
    }
}
