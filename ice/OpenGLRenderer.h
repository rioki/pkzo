// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include "config.h"

#include <rioki/glow/fwd.h>

#include "Renderer.h"
#include "Texture.h"
#include "GraphicSystem.h"

namespace ice
{
    class Texture;
    class OpenGLVideoMemory;

    class ICE_EXPORT OpenGLRenderer : public Renderer
    {
    public:
        OpenGLRenderer(OpenGLVideoMemory& vmem, RendererType type) noexcept;
        ~OpenGLRenderer();

        unsigned int add_camera(const glm::mat4& transform, const glm::uvec2 resolution, const float fov) noexcept override;
        unsigned int add_ortho_camera(const glm::mat4& transform, const glm::vec2& size, const glm::uvec2 resolution) noexcept override;
        void upate_camera_view(unsigned int id, const glm::mat4& transform) noexcept override;
        void upate_camera_projection(unsigned int id, const glm::uvec2 resolution, const float fov) noexcept override;
        void update_camera_ortho_size(unsigned int id, const glm::vec2& size) noexcept override;
        void remove_camera(unsigned int id) noexcept override;

        unsigned int add_ambient_light(const glm::vec3& color) noexcept override;
        unsigned int add_directional_light(const glm::mat4& transform, const glm::vec3& color) noexcept override;
        unsigned int add_point_light(const glm::mat4& transform, const glm::vec3& color) noexcept override;
        unsigned int add_spot_light(const glm::mat4& transform, const glm::vec3& color, const float inner_angle, const float outer_angle) noexcept override;
        unsigned int add_light(LightType type, const glm::mat4& transform, const glm::vec3& color, const float inner_angle, const float outer_angle) noexcept override;
        void update_light_transform(unsigned int id, const glm::mat4& transform) noexcept override;
        void update_light_color(unsigned int id, const glm::vec3& color) noexcept override;
        void update_light_angles(unsigned int id, const float inner_angle, const float outer_angle) noexcept override;
        void remove_light(unsigned int id) noexcept override;

        unsigned int add_geometry(const glm::mat4& transform, const std::shared_ptr<const Mesh>& mesh, const std::shared_ptr<const Material>& material) noexcept;
        void update_geometry_transform(unsigned int id, const glm::mat4& transform) noexcept override;
        void update_geometry_mesh(unsigned int id, const std::shared_ptr<const Mesh>& mesh) noexcept override;
        void update_geometry_material(unsigned int id, const std::shared_ptr<const Material>& material) noexcept override;
        void remove_geometry(unsigned int id) noexcept override;

        void render() const noexcept override;

    private:
        OpenGLVideoMemory& vmem;

        glm::vec2 size = {800.0f, 600.0f};
        std::unique_ptr<glow::Pipeline> pipeline;

        struct Camera
        {
            glm::mat4 projection_matrix;
            glm::mat4 view_matrix;
        };

        unsigned int last_id = 0;
        std::map<unsigned int, Camera>                            cameras;
        std::map<unsigned int, std::shared_ptr<glow::Parameters>> lights;

        std::unique_ptr<glow::Pipeline> create_pipeline(RendererType type) noexcept;
    };
}