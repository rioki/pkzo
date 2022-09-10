// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <memory>
#include <rsig/rsig.h>

#include "System.h"

namespace ice
{
    class Window;
    class Texture;
    class ScreenRenderer;

    class ICE_EXPORT GraphicSystem : public System
    {
    public:
        GraphicSystem(Engine& e);

        ~GraphicSystem();

        Window* get_window() noexcept;
        const Window* get_window() const noexcept;

        const glm::uvec2 get_window_size() const noexcept;

        std::shared_ptr<Texture> get_screenshot() const noexcept;

        ScreenRenderer* create_screen_renderer() noexcept;
        void release_screen_renderer(ScreenRenderer* renderer) noexcept;

        rsig::connection debug_draw(const std::function<void ()>& cb) noexcept;
        rsig::signal<>& get_debug_draw_signal() noexcept;

        void tick() override;

    private:
        std::unique_ptr<Window> window;

        std::vector<std::unique_ptr<ScreenRenderer>> screen_renderers;

        rsig::signal<> debug_draw_signal;

        void render_frame() noexcept;
    };
}
