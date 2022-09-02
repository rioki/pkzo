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

    void GraphicSystem::render_frame() noexcept
    {
        // we are assuming any screen renderer is the overlay screen...
        // a better and more complex implementation will come later
        if (!screen_renderers.empty())
        {
            screen_renderers[0]->render();
        }
    }
}
