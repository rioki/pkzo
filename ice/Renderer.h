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

#include <glm/glm.hpp>

namespace ice
{
    class Mesh;
    class Material;

    enum class LightType
    {
        AMBIENT,
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class ICE_EXPORT Renderer
    {
    public:
        Renderer() noexcept = default;
        virtual ~Renderer() = default;

        virtual unsigned int add_camera(const glm::mat4& transform, const glm::uvec2 resolution, const float fov) noexcept = 0;
        virtual unsigned int add_ortho_camera(const glm::mat4& transform, const glm::vec2& window, const glm::uvec2 resolution) noexcept = 0;
        virtual void upate_camera_view(unsigned int id, const glm::mat4& transform) noexcept = 0;
        virtual void upate_camera_projection(unsigned int id, const glm::uvec2 resolution, const float fov) noexcept = 0;
        virtual void update_camera_ortho_size(unsigned int id, const glm::vec2& size) noexcept = 0;
        virtual void remove_camera(unsigned int id) noexcept = 0;

        virtual unsigned int add_ambient_light(const glm::vec3& color) noexcept = 0;
        virtual unsigned int add_directional_light(const glm::mat4& transform, const glm::vec3& color) noexcept = 0;
        virtual unsigned int add_point_light(const glm::mat4& transform, const glm::vec3& color) noexcept = 0;
        virtual unsigned int add_light(LightType type, const glm::mat4& transform, const glm::vec3& color, const float inner_angle, const float outer_angle) noexcept = 0;
        virtual void update_light_transform(unsigned int id, const glm::mat4& transform) noexcept = 0;
        virtual void update_light_color(unsigned int id, const glm::vec3& color) noexcept = 0;
        virtual void update_light_angles(unsigned int id, const float inner_angle, const float outer_angle) noexcept = 0;
        virtual void remove_light(unsigned int id) noexcept = 0;

        virtual unsigned int add_geometry(const glm::mat4& transform, const std::shared_ptr<const Mesh>& mesh, const std::shared_ptr<const Material>& material) noexcept = 0;
        virtual void update_geometry_transform(unsigned int id, const glm::mat4& transform) noexcept = 0;
        virtual void update_geometry_mesh(unsigned int id, const std::shared_ptr<const Mesh>& mesh) noexcept = 0;
        virtual void update_geometry_material(unsigned int id, const std::shared_ptr<const Material>& material) noexcept = 0;
        virtual void remove_geometry(unsigned int id) noexcept = 0;

        virtual void render() const noexcept = 0;

    private:
        Renderer(const Renderer&) = delete;
        Renderer& operator = (const Renderer&) = delete;
    };
}