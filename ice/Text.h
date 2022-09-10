// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once

#include "ScreenNode.h"
#include "Texture.h"
#include "Font.h"
#include "ScreenRenderer.h"


namespace ice
{
    class ICE_EXPORT Text : public ScreenNode
    {
    public:
        Text(const glm::mat3& transform, const std::string& text, const std::shared_ptr<Font>& font) noexcept;
        Text(const glm::mat3& transform, const std::string& text, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept;

        glm::vec2 get_size() const noexcept;

        void set_text(const std::string& value) noexcept;
        const std::string& get_text() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_font(const std::shared_ptr<Font>& value) noexcept;
        const std::shared_ptr<Font>& get_font() const noexcept;

        void activate() override;
        void deactivate() override;

    private:
        std::string                text;
        std::shared_ptr<Font>      font;
        glm::vec4                  color     = {1.0f, 1.0f, 1.0f, 1.0f};
        std::shared_ptr<Texture>   texture;

        ScreenRenderer::Rectangle* render_handle = nullptr;
    };
}