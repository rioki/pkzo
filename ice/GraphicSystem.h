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

        void tick() override;

    private:
        std::unique_ptr<Window> window;

        void render_frame() noexcept;
    };
}
