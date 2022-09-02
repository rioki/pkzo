// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include "ScreenNode.h"
#include "ScreenRenderer.h"

namespace ice
{
    class Texture;

    class ICE_EXPORT Rectangle : public ScreenNode
    {
    public:
        Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color) noexcept;
        Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture) noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_texture(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_texture() const noexcept;

        void activate() override;
        void deactivate() override;

    private:
        glm::vec2                size      = {15.0f, 15.0f};
        glm::vec4                color     = {1.0f, 1.0f, 1.0f, 1.0f};
        std::shared_ptr<Texture> texture;

        ScreenRenderer::Rectangle* render_handle = nullptr;
    };
}
