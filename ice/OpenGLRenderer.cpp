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

#include "pch.h"
#include "OpenGLRenderer.h"

#include "resource.h"
#include "utils.h"
#include "glm_2d.h" // for glm::transform for 3D
#include "Window.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

namespace ice
{
    constexpr auto MATERIAL_BASE_COLOR = "mat_BaseColor";

    constexpr auto LIGHT_TYPE          = "lgt_Type";
    constexpr auto LIGHT_COLOR         = "lgt_Color";
    constexpr auto LIGHT_DIRECTION     = "lgt_Direction";
    constexpr auto LIGHT_POSITION      = "lgt_Position";
    constexpr auto LIGHT_INNER_ANGLE   = "lgt_InnerAngle";
    constexpr auto LIGHT_OPUTER_ANGLE  = "lgt_OuterAngle";

    OpenGLRenderer::OpenGLRenderer() noexcept = default;
    OpenGLRenderer::~OpenGLRenderer() = default;

    auto create_projection_matrix(const glm::uvec2 resolution, const float hfov)
    {
        auto znear  = 0.1f;
        auto zfar   = 1000.0f;
        auto aspect = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        auto vfov   = std::atan(std::tan(glm::radians(hfov)/2.0f)/aspect);
        // The formula is 2*atan(tan(h/2.0f)/a).
        // OpenGL want's half angle, to prevent *2 /2, the 2* was removed.

        return glm::perspective(vfov, aspect, znear, zfar);
    }

    unsigned int OpenGLRenderer::add_camera(const glm::mat4& transform, const glm::uvec2 resolution, const float fov) noexcept
    {
        auto id = ++last_id;
        cameras[id] = {create_projection_matrix(resolution, fov), glm::inverse(transform)};
        return id;
    }

    void OpenGLRenderer::upate_camera_view(unsigned int id, const glm::mat4& transform) noexcept
    {
        assert(cameras.find(id) != end(cameras));
        cameras[id].view_matrix = glm::inverse(transform);
    }

    void OpenGLRenderer::upate_camera_projection(unsigned int id, const glm::uvec2 resolution, const float fov) noexcept
    {
        assert(cameras.find(id) != end(cameras));
        cameras[id].view_matrix = create_projection_matrix(resolution, fov);
    }

    void OpenGLRenderer::remove_camera(unsigned int id) noexcept
    {
        auto i = cameras.find(id);
        assert(i != end(cameras));
        cameras.erase(i);
    }

    unsigned int OpenGLRenderer::add_ambient_light(const glm::vec3& color) noexcept
    {
        return add_light(LightType::AMBIENT, glm::mat4(1.0f), color, 0.0f, 0.0f);
    }

    unsigned int OpenGLRenderer::add_directional_light(const glm::mat4& transform, const glm::vec3& color) noexcept
    {
        return add_light(LightType::DIRECTIONAL, transform, color, 0.0f, 0.0f);
    }

    unsigned int OpenGLRenderer::add_light(LightType type, const glm::mat4& transform, const glm::vec3& color, const float inner_angle, const float outer_angle) noexcept
    {
        auto direction = glm::normalize(glm::mat3(transform) * glm::vec3(0.0f, 0.0f, -1.0f));
        auto position  = glm::transform(transform, glm::vec3(0.0f));
        auto param = glow::make_shared_parameters({
            {LIGHT_TYPE        , static_cast<glm::uint>(type)},
            {LIGHT_COLOR       , color},
            {LIGHT_DIRECTION   , direction},
            {LIGHT_POSITION    , position},
            {LIGHT_INNER_ANGLE , inner_angle},
            {LIGHT_OPUTER_ANGLE, outer_angle}
        });

        assert(pipeline);
        auto id = pipeline->add_light(param);
        lights[id] = param;
        return id;
    }

    void OpenGLRenderer::update_light_transform(unsigned int id, const glm::mat4& transform) noexcept
    {
        assert(lights.find(id) != end(lights));
        auto direction = glm::normalize(glm::mat3(transform) * glm::vec3(0.0f, 0.0f, -1.0f));
        auto position  = glm::transform(transform, glm::vec3(0.0f));
        lights[id]->set_value(LIGHT_DIRECTION, direction);
        lights[id]->set_value(LIGHT_POSITION,  position);
        pipeline->update_light(id, lights[id]); // this may not be nessesary, but let glow know we changes something
    }

    void OpenGLRenderer::update_light_color(unsigned int id, const glm::vec3& color) noexcept
    {
        assert(lights.find(id) != end(lights));
        lights[id]->set_value(LIGHT_COLOR, color);
        pipeline->update_light(id, lights[id]);
    }

    void OpenGLRenderer::update_light_angles(unsigned int id, const float inner_angle, const float outer_angle) noexcept
    {
        assert(lights.find(id) != end(lights));
        lights[id]->set_value(LIGHT_INNER_ANGLE, inner_angle);
        lights[id]->set_value(LIGHT_OPUTER_ANGLE, outer_angle);
        pipeline->update_light(id, lights[id]);
    }

    void OpenGLRenderer::remove_light(unsigned int id) noexcept
    {
        assert(pipeline);
        pipeline->remove_light(id);

        auto i = lights.find(id);
        assert(i != end(lights));
        lights.erase(i);
    }

    unsigned int OpenGLRenderer::add_geometry(const glm::mat4& transform, const std::shared_ptr<const Mesh>& mesh, const std::shared_ptr<const Material>& material) noexcept
    {
        assert(mesh);
        assert(material);
        assert(pipeline);
        return pipeline->add_geometry(transform, upload(mesh), upload(material));
    }

    void OpenGLRenderer::update_geometry_transform(unsigned int id, const glm::mat4& transform) noexcept
    {
        assert(pipeline);
        return pipeline->update_geometry(id, transform);
    }

    void OpenGLRenderer::update_geometry_mesh(unsigned int id, const std::shared_ptr<const Mesh>& mesh) noexcept
    {
        assert(pipeline);
        return pipeline->update_geometry(id, upload(mesh));
    }

    void OpenGLRenderer::update_geometry_material(unsigned int id, const std::shared_ptr<const Material>& material) noexcept
    {
        assert(pipeline);
        return pipeline->update_geometry(id, upload(material));
    }

    void OpenGLRenderer::remove_geometry(unsigned int id) noexcept
    {
        assert(pipeline);
        return pipeline->remove_geometry(id);
    }

    void OpenGLRenderer::render() const noexcept
    {
        assert(pipeline);
        assert(!cameras.empty());

        auto c = cameras.begin()->second;

        pipeline->set_camera(c.projection_matrix, c.view_matrix);
        pipeline->execute();
    }

    // Implemented in ScreenRenderer.cpp; should be refactoried anyway.
    std::string LoadTextResource(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType);
    std::shared_ptr<glow::Shader> load_shader(HMODULE hModule, unsigned int rcid);

    std::unique_ptr<glow::Pipeline> OpenGLRenderer::create_pipeline()
    {
        try
        {
            HMODULE hModule = GetModuleHandleW(L"ice.dll");
            assert(hModule);

            auto pipeline = std::make_unique<glow::Pipeline>();

            pipeline->add_pass(glow::PassType::GEOMETRY_AND_LIGHTS, load_shader(hModule, IDR_GLSL_FORWARD_SOLID_GEOMETRY), glow::DepthTest::ON, glow::Blending::MULTIPASS);

            return pipeline;
        }
        // This should only happen in development
        catch (const std::exception& ex)
        {
            show_message_box(MessageBoxIcon::ERROR, "GLSL Compile Error", ex.what());
            std::abort();
        }
    }

    std::shared_ptr<glow::VertexBuffer> OpenGLRenderer::upload(const std::shared_ptr<const Mesh>& mesh) noexcept
    {
        // TODO centralize video memory

        auto buffer = std::make_shared<glow::VertexBuffer>();
        buffer->upload_values(glow::VERTEX,   mesh->get_vertices());
        buffer->upload_values(glow::NORMAL,   mesh->get_normals());
        //buffer->upload_values(glow::TANGENT,   mesh->get_tangents());
        buffer->upload_values(glow::TEXCOORD, mesh->get_texcoords());
        buffer->upload_indexes(mesh->get_faces());

        return buffer;
    }

    std::shared_ptr<glow::Texture> OpenGLRenderer::upload(const std::shared_ptr<const Texture>& texture) noexcept
    {
        // TODO centralize video memory

        auto size   = texture->get_size();
        auto color  = static_cast<glow::ColorMode>(texture->get_color_mode());
        auto data   = static_cast<glow::DataType>(texture->get_data_type());
        auto bits   = texture->get_data();
        auto filter = static_cast<glow::FilterMode>(texture->get_filter_mode());
        auto wrap   = static_cast<glow::WrapMode>(texture->get_wrap_mode());

        auto gl_texture = std::make_shared<glow::Texture>();
        gl_texture->upload_2d(size, color, data, bits, filter, wrap);
        return gl_texture;
    }

    std::shared_ptr<glow::Parameters> OpenGLRenderer::upload(const std::shared_ptr<const Material>& material) noexcept
    {
        // TODO centralize video memory

        return glow::make_shared_parameters({
            {MATERIAL_BASE_COLOR, material->get_base_color()}
            // TODO more material parameters
        });
    }
}
