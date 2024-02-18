// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <glm/glm.hpp>
#include <glow/glow.h>

#include "defines.h"
#include "Mesh.h"
#include "Material.h"

namespace pkzo
{
    class PKZO_EXPORT Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void set_resolution(const glm::uvec2& resolution);
        void set_camera(const glm::mat4& transform, float fov);

        unsigned int add_mesh_geometry(glm::mat4 transform, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
        unsigned int add_box_geometry(glm::mat4 transform, glm::vec3 size, const std::shared_ptr<Material>& material);
        unsigned int add_sphere_geometry(glm::mat4 transform, float diameter, const std::shared_ptr<Material>& material);

        void remove_geometry(unsigned int id);

        unsigned int add_ambient_light(glm::vec3 color);
        unsigned int add_directional_light(glm::vec3 color, glm::vec3 direction);
        unsigned int add_point_light(glm::vec3 color, glm::vec3 position, float radius);
        unsigned int add_spot_light(glm::vec3 color, glm::vec3 position, glm::vec3 direction, float radius, float angle);

        void remove_light(unsigned int id);

        void execute();

    private:
        std::unique_ptr<glow::Pipeline>    pipeline;
        std::shared_ptr<glow::FrameBuffer> geometry_buffer;

        std::shared_ptr<Mesh> box_mesh;
        std::shared_ptr<Mesh> sphere_mesh;

        std::shared_ptr<glow::Parameters> global_params = std::make_shared<glow::Parameters>();
        std::map<std::shared_ptr<Mesh>, std::shared_ptr<glow::VertexBuffer>> mesh_cache;
        std::map<std::shared_ptr<Image>, std::shared_ptr<glow::Texture>>     texture_cache;

        std::shared_ptr<glow::VertexBuffer> upload_mesh(const std::shared_ptr<Mesh>& mesh);
        std::shared_ptr<glow::Parameters>   upload_material(const std::shared_ptr<Material>& material);
        std::shared_ptr<glow::Texture>      upload_texture(const std::shared_ptr<Image>& image);

        void collect_garbage();

        Renderer(const Renderer&) = delete;
        Renderer& operator = (const Renderer&) = delete;
    };
}
