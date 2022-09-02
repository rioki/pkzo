// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <glm/glm.hpp>
#include <rioki/glow/Pipeline.h>

#include "Texture.h"

namespace ice
{
    class ICE_EXPORT ScreenRenderer
    {
    public:
        class Rectangle
        {
        public:
            Rectangle(glow::Pipeline& pipeline, const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture) noexcept;
            ~Rectangle();

            void set_transform(const glm::mat3& value) noexcept;
            const glm::mat3& get_transform() const noexcept;

            void set_size(const glm::vec2& value) noexcept;
            const glm::vec2& get_size() const noexcept;

            void set_color(const glm::vec4& value) noexcept;
            const glm::vec4& get_color() const noexcept;

            void set_texture(const std::shared_ptr<Texture>& value) noexcept;
            const std::shared_ptr<Texture>& get_texture() const noexcept;

        private:
            glow::Pipeline&          pipeline;
            unsigned int             handle    = 0;

            glm::mat3                transform;
            glm::vec2                size;
            glm::vec4                color;
            std::shared_ptr<Texture> texture;

            glm::mat4 create_3d_transform() const noexcept;
            static std::shared_ptr<glow::VertexBuffer> create_unit_rectangle();
            std::shared_ptr<glow::Parameters> create_parameters() const noexcept;

            Rectangle(const Rectangle&) = delete;
            Rectangle& operator = (const Rectangle&) = delete;
        };

        ScreenRenderer() noexcept;

        ~ScreenRenderer();

        void set_screen_size(const glm::vec2& size);

        Rectangle* add_rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture);

        void remove_geometry(Rectangle* rectangle);

        void render();

    private:
        glm::vec2 size = {800.0f, 600.0f};
        std::unique_ptr<glow::Pipeline> pipeline = create_pipeline();

        std::vector<std::unique_ptr<Rectangle>> geometries;

        static std::unique_ptr<glow::Pipeline> create_pipeline();

        ScreenRenderer(const ScreenRenderer&) = delete;
        ScreenRenderer& operator = (const ScreenRenderer&) = delete;
    };
}