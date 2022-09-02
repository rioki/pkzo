// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <memory>

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

        [[nodiscard]]
        Window* get_window() noexcept;
        [[nodiscard]]
        const Window* get_window() const noexcept;

        [[nodiscard]] std::shared_ptr<Texture> get_screenshot() const noexcept;

        [[nodiscard]] ScreenRenderer* create_screen_renderer() noexcept;
        void release_screen_renderer(ScreenRenderer* renderer) noexcept;

        void tick() override;

    private:
        std::unique_ptr<Window> window;

        std::vector<std::unique_ptr<ScreenRenderer>> screen_renderers;

        void render_frame() noexcept;
    };
}
