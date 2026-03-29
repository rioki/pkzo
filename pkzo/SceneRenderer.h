// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include <map>
#include <memory>

#include <pkzo/GraphicContext.h>
#include <pkzo/Shader.h>
#include <pkzo/CubeMap.h>
#include <pkzo/Mesh.h>

#include "api.h"

namespace pkzo
{
    class Camera;
    class SkyBox;
    class Geometry;
    class Light;
    class Material;

    using pkzo::GraphicContext;
    using pkzo::Shader;
    using pkzo::CubeMap;
    using pkzo::Mesh;

    class PKZO_EXPORT SceneRenderer
    {
    public:
        SceneRenderer();

        ~SceneRenderer();

        void add_debug_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
        void add_debug_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color);

        void add(Camera* camera);
        void remove(Camera* camera);

        void add(SkyBox* sky_box);
        void remove(SkyBox* sky_box);

        void add(Geometry* geometry);
        void remove(Geometry* geometry);

        void add(Light* light);
        void remove(Light* light);

        void render(GraphicContext& gc);

    private:
        std::vector<Camera*>   cameras;
        std::vector<SkyBox*>   skyboxes;
        std::vector<Geometry*> geometries;
        std::vector<Light*>    lights;

        std::shared_ptr<Shader> forward_shader;
        std::shared_ptr<Shader> skybox_shader;
        std::shared_ptr<Shader> cubemap_generator_shader;
        std::shared_ptr<Shader> cubemap_diffuse_filter_shader;
        std::shared_ptr<Shader> cubemap_specular_filter_shader;

        struct IblMaps
        {
            std::shared_ptr<CubeMap> diffuse;
            std::shared_ptr<CubeMap> specular;
        };
        std::map<std::weak_ptr<CubeMap>, IblMaps, std::owner_less<>> ibl_cache;

        struct LineRenderer
        {
            std::vector<glm::vec3>  line_vertexes;
            std::vector<glm::vec4>  line_colors;
            std::vector<glm::uvec2> line_indexes;

            std::shared_ptr<Mesh>   line_vertex_buffer;
            std::shared_ptr<Shader> line_shader;

            void add_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color);

            void render(GraphicContext& gc, const Camera* camera);

        } debug_line_renderer;

        void load_shaders(GraphicContext& gc);
        IblMaps genrate_ibl_maps(GraphicContext& gc, const std::shared_ptr<CubeMap>& light_probe);
        void apply_light(GraphicContext& gc, int i, const Light* light);
        void apply_light_probe(GraphicContext& gc, int i, const std::shared_ptr<CubeMap>& probe);
        void apply_material(GraphicContext& gc, const std::shared_ptr<Material>& material);
        void render_skybox(GraphicContext& gc);
        void render_forward(GraphicContext& gc);

        SceneRenderer(const SceneRenderer&) = delete;
        SceneRenderer& operator = (const SceneRenderer&) = delete;
    };
}
