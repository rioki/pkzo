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

#include "pch.h"
#include "Renderer.h"
#include "resource.h"

namespace pkzo
{
    enum class LightType
    {
        AMBIENT,
        DIRECTIONAL,
        POINT,
        SPOT
    };

    std::shared_ptr<Mesh> create_box_mesh(const glm::vec3& size)
    {
        auto mesh = std::make_shared<Mesh>();

        auto hs = size / 2.0f;

        // position, normal, tangent, texcoord
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});

        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});

        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});

        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});

        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f});

        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f});

        mesh->add_triangle(0, 1, 2);
        mesh->add_triangle(0, 2, 3);

        mesh->add_triangle(4, 5, 6);
        mesh->add_triangle(4, 6, 7);

        mesh->add_triangle(8, 9, 10);
        mesh->add_triangle(8, 10, 11);

        mesh->add_triangle(12, 13, 14);
        mesh->add_triangle(12, 14, 15);

        mesh->add_triangle(16, 17, 18);
        mesh->add_triangle(16, 18, 19);

        mesh->add_triangle(20, 21, 22);
        mesh->add_triangle(20, 22, 23);

        return mesh;
    }

    std::shared_ptr<Mesh> create_sphere_mesh(float diameter, unsigned int sectors, unsigned int rings)
    {
        auto mesh = std::make_shared<Mesh>();

        auto radius = diameter / 2.0f;

        for (unsigned int r = 0; r <= rings; r++)
        {
            auto v = static_cast<float>(r) / static_cast<float>(rings);
            auto phi = glm::pi<float>() * v;

            for (unsigned int s = 0; s <= sectors; s++)
            {
                auto u = static_cast<float>(s) / static_cast<float>(sectors);
                auto theta = glm::two_pi<float>() * u;

                auto x = std::cos(theta) * std::sin(phi);
                auto y = std::sin(theta) * std::sin(phi);
                auto z = std::cos(phi);

                auto normal = glm::vec3(x, y, z);
                auto tangent = glm::vec3(-std::sin(theta), std::cos(theta), 0.0f);
                auto texcoord = glm::vec2(u, v);

                mesh->add_vertex(normal * radius, normal, tangent, texcoord);
            }
        }

        for (unsigned int r = 0; r < rings; r++)
        {
            for (unsigned int s = 0; s < sectors; s++)
            {
                auto i0 = (r + 0) * (sectors + 1) + (s + 0);
                auto i1 = (r + 1) * (sectors + 1) + (s + 0);
                auto i2 = (r + 1) * (sectors + 1) + (s + 1);
                auto i3 = (r + 0) * (sectors + 1) + (s + 1);

                mesh->add_triangle(i0, i1, i2);
                mesh->add_triangle(i0, i2, i3);
            }
        }

        return mesh;
    }

    std::string LoadTextResource(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType)
    {
        auto hRSrc = FindResourceW(hModule, lpName, lpType);
        check(hRSrc);
        auto hGlobal = LoadResource(hModule, hRSrc);
        check(hGlobal);
        auto nSize = SizeofResource(hModule, hRSrc);
        auto psCode = reinterpret_cast<const char*>(LockResource(hGlobal));
        return std::string(psCode, nSize);
    }

    std::shared_ptr<glow::Shader> create_shader(unsigned int vertex_rcid, unsigned int fragment_rcid)
    {
        static auto handle = GetModuleHandleW(L"pkzo.dll");

        auto vertex_code = LoadTextResource(handle, MAKEINTRESOURCEW(vertex_rcid), L"GLSL");
        auto fragment_code = LoadTextResource(handle, MAKEINTRESOURCEW(fragment_rcid), L"GLSL");

        auto shader = std::make_shared<glow::Shader>();
        shader->compile(glow::ShaderType::VERTEX, vertex_code);
        shader->compile(glow::ShaderType::FRAGMENT, fragment_code);
        shader->link();
        return shader;
    }

    const auto geometry_buffer_config = std::vector<glow::BufferConfig>{
        {"uPosition",  "oPosition",  glow::ColorMode::RGBA,  glow::DataType::FLOAT},
        {"uNormal",    "oNormal",    glow::ColorMode::RGBA,  glow::DataType::FLOAT},
        {"uBaseColor", "oBaseColor", glow::ColorMode::RGBA,  glow::DataType::UINT8},
        {"uMRHA",      "oMRHA",      glow::ColorMode::RGBA,  glow::DataType::UINT8},
        {"uEmissive",  "oEmissive",  glow::ColorMode::RGBA,  glow::DataType::UINT8},
        {"uDepth",     "",           glow::ColorMode::DEPTH, glow::DataType::FLOAT}
    };

    Renderer::Renderer()
    {
        pipeline = std::make_unique<glow::Pipeline>();

        geometry_buffer = std::make_shared<glow::FrameBuffer>(glm::uvec2(800, 600), geometry_buffer_config);

        pipeline->add_pass("Geometry Pass", glow::PassType::GEOMETRY, geometry_buffer, create_shader(IDR_GLSL_GEOMETRY_VERTEX, IDR_GLSL_GEOMETRY_FRAGMENT), glow::DepthTest::ON, glow::Blending::OFF);
        pipeline->add_pass("Lighting Pass", glow::PassType::LIGHTS, create_shader(IDR_GLSL_LIGHTING_VERTEX, IDR_GLSL_LIGHTING_FRAGMENT), glow::DepthTest::OFF, glow::Blending::MULTIPASS, geometry_buffer->get_input_parameters());
        //pipeline->add_pass("Debug", glow::PassType::FULLSCREEN, create_shader(IDR_GLSL_DEBUG_VERTEX, IDR_GLSL_DEBUG_FRAGMENT), glow::DepthTest::OFF, glow::Blending::OFF, geometry_buffer->get_input_parameters());

        set_resolution({800, 600});
        set_camera(glm::mat4(1.0f), 90.0f);
    }

    Renderer::~Renderer() = default;

    void Renderer::set_resolution(const glm::uvec2& resolution)
    {
        global_params->set_value("uResolution", resolution);
        pipeline->set_parameters(global_params);

        if (resolution != geometry_buffer->get_size())
        {
            geometry_buffer->resize(resolution);
        }
    }

    void Renderer::set_camera(const glm::mat4& transform, float fov)
    {
        auto resolution = std::get<glm::uvec2>(global_params->get_value("uResolution"));
        auto znear  = 0.1f;
        auto zfar   = 1000.0f; // TODO compute based on scene
        auto aspect = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        auto vfov   = std::atan(std::tan(glm::radians(fov)/2.0f)/aspect);
        // The formula is 2*atan(tan(h/2.0f)/a).
        // OpenGL wants half angle, to prevent *2 /2, the 2* was removed.

        auto projection = glm::perspective(vfov, aspect, znear, zfar);
        auto view       = glm::inverse(transform);

        global_params->set_value("uProjection", projection);
        global_params->set_value("uView", view);
        global_params->set_value("uCameraPosition", glm::vec3(transform[3]));
        pipeline->set_parameters(global_params);
    }

    unsigned int Renderer::add_mesh_geometry(glm::mat4 transform, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
    {
        check(mesh);
        check(material);

        auto buffer = upload_mesh(mesh);
        auto params = upload_material(material);
        params->set_value("uModel", transform);

        return pipeline->add_geometry(buffer, params);
    }

    unsigned int Renderer::add_box_geometry(glm::mat4 transform, glm::vec3 size, const std::shared_ptr<Material>& material)
    {
        check(material);

        if (box_mesh == nullptr)
        {
            box_mesh = create_box_mesh(glm::vec3(1.0f));
        }

        auto t = glm::scale(transform, size);

        return add_mesh_geometry(t, box_mesh, material);
    }

    unsigned int Renderer::add_sphere_geometry(glm::mat4 transform, float diameter, const std::shared_ptr<Material>& material)
    {
        check(material);

        if (sphere_mesh == nullptr)
        {
            sphere_mesh = create_sphere_mesh(1.0f, 16, 16);
        }

        auto t = glm::scale(transform, glm::vec3(diameter));

        return add_mesh_geometry(t, sphere_mesh, material);
    }

    void Renderer::remove_geometry(unsigned int id)
    {
        pipeline->remove_geometry(id);
    }

    unsigned int Renderer::add_ambient_light(glm::vec3 color)
    {
        auto param = glow::make_shared_parameters({
            {"uLightType",  rex::to_underlying(LightType::AMBIENT)},
            {"uLightColor", color},
            {"uLightId",    pipeline->get_light_count()}
        });
        return pipeline->add_light(param);
    }

    unsigned int Renderer::add_directional_light(glm::vec3 color, glm::vec3 direction)
    {
        auto param = glow::make_shared_parameters({
            {"uLightType",      rex::to_underlying(LightType::DIRECTIONAL)},
            {"uLightColor",     color},
            {"uLightDirection", direction},
            {"uLightId",        pipeline->get_light_count()}
        });
        return pipeline->add_light(param);
    }

    unsigned int Renderer::add_point_light(glm::vec3 color, glm::vec3 position, float radius)
    {
        auto param = glow::make_shared_parameters({
            {"uLightType",     rex::to_underlying(LightType::POINT)},
            {"uLightColor",    color},
            {"uLightPosition", position},
            {"uLightRadius",   radius},
            {"uLightId",       pipeline->get_light_count()}
        });
        return pipeline->add_light(param);
    }

    unsigned int Renderer::add_spot_light(glm::vec3 color, glm::vec3 position, glm::vec3 direction, float radius, float angle)
{
        auto param = glow::make_shared_parameters({
            {"uLightType",      rex::to_underlying(LightType::SPOT)},
            {"uLightColor",     color},
            {"uLightPosition",  position},
            {"uLightDirection", direction},
            {"uLightRadius",    radius},
            {"uLightAngle",     angle},
            {"uLightId",        pipeline->get_light_count()}
        });
        return pipeline->add_light(param);
    }

    void Renderer::remove_light(unsigned int id)
    {
        pipeline->remove_light(id);
    }

    void Renderer::execute()
    {
        pipeline->execute();
        collect_garbage();
    }

    std::shared_ptr<glow::VertexBuffer> Renderer::upload_mesh(const std::shared_ptr<Mesh>& mesh)
    {
        check(mesh);
        auto i = mesh_cache.find(mesh);
        if (i != mesh_cache.end())
        {
            return i->second;
        }
        else
        {
            auto buffer = std::make_shared<glow::VertexBuffer>();
            buffer->upload_values("aPosition", mesh->get_positions());
            buffer->upload_values("aNormal", mesh->get_normals());
            buffer->upload_values("aTangent", mesh->get_tangents());
            buffer->upload_values("aTexCoord", mesh->get_texcoords());
            buffer->upload_indexes(mesh->get_triangles());

            mesh_cache[mesh] = buffer;

            return buffer;
        }
    }

    std::shared_ptr<glow::Parameters> Renderer::upload_material(const std::shared_ptr<Material>& material)
    {
        check(material);
        auto params = std::make_shared<glow::Parameters>();
        params->set_value("uBaseColorFactor", material->get_base_color_factor());
        params->set_value("uMetallicFactor", material->get_metallic_factor());
        params->set_value("uRoughnessFactor", material->get_roughness_factor());
        params->set_value("uEmissiveFactor", material->get_emissive_factor());

        if (material->get_base_color_map())
        {
            params->set_value("uHasBaseColorMap", true);
            params->set_value("uBaseColorMap", upload_texture(material->get_base_color_map()));
        }
        else
        {
            params->set_value("uHasBaseColorMap", false);
        }

        if (material->get_metallic_roughness_map())
        {
            params->set_value("uHasMetallicRoughnessMap", true);
            params->set_value("uMetallicRoughnessMap", upload_texture(material->get_metallic_roughness_map()));
        }
        else
        {
            params->set_value("uHasMetallicRoughnessMap", false);
        }

        if (material->get_emissive_map())
        {
            params->set_value("uHasEmissiveMap", true);
            params->set_value("uEmissiveMap", upload_texture(material->get_emissive_map()));
        }
        else
        {
            params->set_value("uHasEmissiveMap", false);
        }

        if (material->get_normal_map())
        {
            params->set_value("uHasNormalMap", true);
            params->set_value("uNormalMap", upload_texture(material->get_normal_map()));
        }
        else
        {
            params->set_value("uHasNormalMap", false);
        }

        return params;
    }

    glow::ColorMode to_glow(const pkzo::ColorMode& mode)
    {
        switch (mode)
        {
            case pkzo::ColorMode::RGB:
                return glow::ColorMode::RGB;
            case pkzo::ColorMode::BGR:
                return glow::ColorMode::BGR;
            case pkzo::ColorMode::RGBA:
                return glow::ColorMode::RGBA;
            case pkzo::ColorMode::BGRA:
                return glow::ColorMode::BGRA;
            default:
                fail();
                return glow::ColorMode::RGBA;
        }
    }

    std::shared_ptr<glow::Texture> Renderer::upload_texture(const std::shared_ptr<Image>& image)
    {
        check(image);
        auto i = texture_cache.find(image);
        if (i != texture_cache.end())
        {
            return i->second;
        }
        else
        {
            auto color = to_glow(image->get_color_mode());
            auto type  = glow::DataType::UINT8;

            auto texture = std::make_shared<glow::Texture>();
            texture->upload(image->get_size(), color, type, image->get_data());
            texture_cache[image] = texture;
            return texture;
        }
    }

    void Renderer::collect_garbage()
    {
        std::erase_if(mesh_cache, [](auto& pair) { return pair.first.use_count() == 1; });
        std::erase_if(texture_cache, [](auto& pair) { return pair.first.use_count() == 1; });
    }

}
