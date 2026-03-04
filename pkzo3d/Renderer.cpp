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

#include "Renderer.h"

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <map>
#include <numbers>

#include <magic_enum/magic_enum.hpp>
#include <tinyformat.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <pkzo/debug.h>

#include "resource.h"
#include "SkyBox.h"
#include "Camera.h"
#include "Geometry.h"
#include "Light.h"
#include "Material.h"
#include <pkzo/OpenGLMesh.h>

namespace pkzo3d
{
    using pkzo::check;
    using pkzo::trace;
    using pkzo::GraphicContext;

    constexpr int MAX_LIGHTS = 4;
    constexpr int MAX_LIGHT_PROBES = 1;

    #ifdef _WIN32
    std::string LoadTextResource(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType) noexcept
    {
        auto hRSrc = FindResourceW(hModule, lpName, lpType);
        check(hRSrc);

        auto hGlobal = LoadResource(hModule, hRSrc);
        check(hGlobal);

        auto nSize = SizeofResource(hModule, hRSrc);
        auto psCode = reinterpret_cast<const char*>(LockResource(hGlobal));
        return std::string(psCode, nSize);
    }
    #endif

    std::string load_glsl_source(unsigned int id)
    {
        #ifdef _WIN32
        auto handle = GetModuleHandleW(L"pkzo3d.dll");
        check(handle);

        auto code = LoadTextResource(handle, MAKEINTRESOURCEW(id), L"GLSL");
        check(!code.empty());

        return code;
        #else
        #error Port Me
        #endif
    }

    enum class UniformLocation : int
    {
        // Cubemap/Texture Generator & Filter
        MIPLEVEL        = pkzo::GeneratorUniformLocation::MIPLEVEL,
        TEXTURE         = pkzo::GeneratorUniformLocation::TEXTURE,
        CUBEMAP         = pkzo::GeneratorUniformLocation::CUBEMAP,
        CUBEMAP_TBN     = pkzo::GeneratorUniformLocation::CUBEMAP_TBN,

        // Tansforms
        PROJECTION_MATRIX,
        VIEW_MATRIX,
        MODEL_MATRIX,
        // Material
        BASE_COLOR_FACTOR,
        BASE_COLOR_MAP,
        METALLIC_FACTOR,
        ROUGHNESS_FACTOR,
        METALLIC_ROUGHNESS_MAP,
        NORMAL_MAP,
        EMISSIVE_FACTOR,
        EMISSIVE_MAP,
        // Light
        LIGHT0_TYPE,
        LIGHT0_DIRECTION,
        LIGHT0_POSITION,
        LIGHT0_COLOR,
        LIGHT0_ANGLES,
        LIGHT1_TYPE,
        LIGHT1_DIRECTION,
        LIGHT1_POSITION,
        LIGHT1_COLOR,
        LIGHT1_ANGLES,
        LIGHT2_TYPE,
        LIGHT2_DIRECTION,
        LIGHT2_POSITION,
        LIGHT2_COLOR,
        LIGHT2_ANGLES,
        LIGHT3_TYPE,
        LIGHT3_DIRECTION,
        LIGHT3_POSITION,
        LIGHT3_COLOR,
        LIGHT3_ANGLES,
        SHADOW_MAP,
        // SkyBox & Light Probes
        ENVIRONMENT,
        LIGHT_PROBE0_ENABLED,
        LIGHT_PROBE0_ENVIRONMENT,
        LIGHT_PROBE0_DIFFUSE,
        LIGHT_PROBE0_SPECULAR
    };

    const auto legal = "// pkzo\n"
                       "// Copyright 2010-2026 Sean Farrell\n"
                       "//\n"
                       "// Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                       "// of this software and associated documentation files(the \"Software\"), to deal\n"
                       "// in the Software without restriction, including without limitation the rights\n"
                       "// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                       "// copies of the Software, and to permit persons to whom the Software is\n"
                       "// furnished to do so, subject to the following conditions :\n"
                       "//\n"
                       "// The above copyright notice and this permission notice shall be included in all\n"
                       "// copies or substantial portions of the Software.\n"
                       "//\n"
                       "// THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                       "// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                       "// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\n"
                       "// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                       "// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                       "// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                       "// SOFTWARE.\n"
                       "\n"
                       "// This file is generated, do not edit.\n"
                       "\n";
    const auto light_struct = "struct Light\n"
                              "{\n"
                              "    int type;\n"
                              "    vec3 direction;\n"
                              "    vec3 position;\n"
                              "    vec3 color;\n"
                              "    vec2 angles;\n"
                              "};\n";
    const auto light_probe_struct = "struct LightProbe\n"
                              "{\n"
                              "    int enabled;\n"
                              "    samplerCube environment;\n"
                              "    samplerCube diffuse;\n"
                              "    samplerCube specular;\n"
                              "};\n";

    using pkzo::AttributeLocation;

    struct AttribSpec
    {
        AttributeLocation location;
        std::string       type;
        std::string       id;
    };
    const auto attributes = std::vector<AttribSpec>{
        {AttributeLocation::VERTEX,   "vec3", "atr_Vertex"},
        {AttributeLocation::NORMAL,   "vec3", "atr_Normal"},
        {AttributeLocation::TANGENT,  "vec3", "atr_Tangent"},
        {AttributeLocation::TEXCOORD, "vec2", "atr_TexCoord"},
        {AttributeLocation::COLOR,    "vec4", "atr_Color"}
    };

    struct UniformSpec
    {
        UniformLocation location;
        std::string     type;
        std::string     id;
        unsigned int    size = 0; // 0 == scalar
    };
    const auto uniforms = std::vector<UniformSpec>{
        // Texture / Cubemap Generation & Filter
        {UniformLocation::MIPLEVEL,               "int",         "uni_MipLevel"},
        {UniformLocation::TEXTURE,                "sampler2D",   "uni_Texture"},
        {UniformLocation::CUBEMAP,                "samplerCube", "uni_CubeMap"},
        {UniformLocation::CUBEMAP_TBN,            "mat3",        "uni_CubemapTBN"},
        // Tansforms
        {UniformLocation::PROJECTION_MATRIX,      "mat4",        "uni_ProjectionMatrix"},
        {UniformLocation::VIEW_MATRIX,            "mat4",        "uni_ViewMatrix"},
        {UniformLocation::MODEL_MATRIX,           "mat4",        "uni_ModelMatrix"},
        // Material
        {UniformLocation::BASE_COLOR_FACTOR,      "vec4",        "uni_BaseColorFactor"},
        {UniformLocation::BASE_COLOR_MAP,         "sampler2D",   "uni_BaseColorMap"},
        {UniformLocation::METALLIC_FACTOR,        "float",       "uni_MetallicFactor"},
        {UniformLocation::ROUGHNESS_FACTOR,       "float",       "uni_RoughnessFactor"},
        {UniformLocation::METALLIC_ROUGHNESS_MAP, "sampler2D",   "uni_MetallicRoughnessMap"},
        {UniformLocation::NORMAL_MAP,             "sampler2D",   "uni_NormalMap"},
        {UniformLocation::EMISSIVE_FACTOR,        "vec3",        "uni_EmissiveFactor"},
        {UniformLocation::EMISSIVE_MAP,           "sampler2D",   "uni_EmissiveMap"},
        // Light
        {UniformLocation::LIGHT0_TYPE,            "Light",       "uni_Light", MAX_LIGHTS},
        {UniformLocation::SHADOW_MAP,             "sampler2D",   "uni_ShadowMap"},
        // Skybox / Environment Lighting
        {UniformLocation::ENVIRONMENT,            "samplerCube", "uni_Environment"},
        {UniformLocation::LIGHT_PROBE0_ENABLED,   "LightProbe",  "uni_LightProbes", MAX_LIGHT_PROBES}
    };

    #ifdef DEV_BUILD
    // DESIGN: Writing the include files from the lib is a bit nasty, but it does the trick.
    // Internally these files are not used, just for IDE's libter.
    void write_include_file(const std::string& filename, const std::string& contents)
    {
        auto inc_file = std::filesystem::path(SOLUTION_DIR) / "pkzo3d" / filename;
        if (std::filesystem::exists(inc_file))
        {
            auto output = std::ofstream(inc_file);
            output << contents;
        }
    }
    #endif

    auto make_uniforms_include()
    {
        auto result = std::stringstream{};

        result << legal;

        result << tfm::format("#define MAX_LIGHTS %d\n", MAX_LIGHTS);
        for (auto lt : magic_enum::enum_values<LightType>())
        {
            result << tfm::format("#define %s_LIGHT %d\n", magic_enum::enum_name(lt), std::to_underlying(lt));
        }
        result << "\n";
        result << tfm::format("#define MAX_LIGHT_PROBES %d\n", MAX_LIGHT_PROBES);
        result << "\n";
        for (auto lt : magic_enum::enum_values<pkzo::CubeFace>())
        {
            result << tfm::format("#define %s %d\n", magic_enum::enum_name(lt), std::to_underlying(lt));
        }
        result << "\n";

        result << light_struct;
        result << "\n";

        result << light_probe_struct;
        result << "\n";


        for (const auto& uniform : uniforms)
        {
            if (uniform.size == 0)
            {
                result << tfm::format("layout(location = %d) uniform %s %s;\n", std::to_underlying(uniform.location), uniform.type, uniform.id);
            }
            else
            {
                result << tfm::format("layout(location = %d) uniform %s %s[%d];\n", std::to_underlying(uniform.location), uniform.type, uniform.id, uniform.size);
            }
        }

        #ifdef DEV_BUILD
        write_include_file("uniforms.glsl", result.str());
        #endif

        return result.str();
    }

    auto make_attribute_include()
    {
        auto result = std::stringstream{};

        result << legal;

        for (const auto& attribute : attributes)
        {
            result << tfm::format("layout(location = %d) in %s %s;\n", std::to_underlying(attribute.location), attribute.type, attribute.id);
        }

        #ifdef DEV_BUILD
        write_include_file("attributes.glsl", result.str());
        #endif

        return result.str();
    }

    auto make_outputs_include()
    {
        auto result = std::stringstream{};

        result << legal;

        for (auto i = 0u; i < 8u; i++)
        {
            result << tfm::format("layout(location = %d) out vec4 out_FragColor%d;\n", i, i);
        }

        #ifdef DEV_BUILD
        write_include_file("outputs.glsl", result.str());
        #endif

        return result.str();
    }

    const auto virtual_files = std::map<std::string, std::string>{
        {"attributes.glsl", make_attribute_include()},
        {"uniforms.glsl", make_uniforms_include()},
        {"outputs.glsl", make_outputs_include()},
        {"math.glsl", load_glsl_source(IDR_GLSL_MATH)},
    };

    std::string expand_includes(const std::string_view src, int depth = 0)
    {
        if (depth > 32)
        {
            throw std::runtime_error("include recursion too deep");
        }

        auto result = std::stringstream{};

        size_t pos = 0;
        size_t line_num = 1;
        while (pos < src.size())
        {
            auto line_end = src.find('\n', pos);
            if (line_end == std::string_view::npos) line_end = src.size();

            std::string_view line = src.substr(pos, line_end - pos);

            auto inc = line.find("#include");
            if (inc != std::string_view::npos)
            {
                auto q1 = line.find('"', inc);
                auto q2 = (q1 == std::string_view::npos) ? q1 : line.find('"', q1 + 1);
                if (q1 != std::string_view::npos && q2 != std::string_view::npos && q2 > q1 + 1)
                {
                    std::string name(line.substr(q1 + 1, q2 - (q1 + 1)));
                    auto it = virtual_files.find(name);
                    if (it == virtual_files.end())
                    {
                        throw std::runtime_error("Unknown include: " + name);
                    }

                    result << "\n#line 1\n";
                    result << expand_includes(it->second, depth + 1);
                    result << "\n#line " << line_num << "\n";
                }
                else
                {
                    result.write(line.data(), line.size());
                }
            }
            else
            {
                result.write(line.data(), line.size());
            }

            if (line_end < src.size())
            {
                result << '\n';
            }
            pos = line_end + 1;
            line_num++;
        }

        return result.str();
    }

    std::string load_glsl_resource(unsigned int id)
    {
        auto code = load_glsl_source(id);
        return expand_includes(code);
    }

    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::add_debug_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {
        debug_line_renderer.add_line(start, end, color, color);
    }

    void Renderer::add_debug_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color)
    {
        debug_line_renderer.add_line(start, end, start_color, end_color);
    }

    void Renderer::add(Camera* camera)
    {
        cameras.push_back(camera);
    }

    void Renderer::remove(Camera* camera)
    {
        std::erase(cameras, camera);
    }

    void Renderer::add(SkyBox* sky_box)
    {
        skyboxes.push_back(sky_box);
    }

    void Renderer::remove(SkyBox* sky_box)
    {
        std::erase(skyboxes, sky_box);
    }

    void Renderer::add(Geometry* geometry)
    {
        geometries.push_back(geometry);
    }

    void Renderer::remove(Geometry* geometry)
    {
        std::erase(geometries, geometry);
    }

    void Renderer::add(Light* light)
    {
        lights.push_back(light);
    }

    void Renderer::remove(Light* light)
    {
        std::erase(lights, light);
    }

    void Renderer::render(pkzo::GraphicContext& gc)
    {
        if (!cameras.empty() && !geometries.empty())
        {
            load_shaders(gc);

            auto viewport = gc.get_viewport();
            check(cameras.size() == 1);
            auto* camera = cameras[0];
            camera->set_resolution({viewport.size.x, viewport.size.y});

            if (!skyboxes.empty())
            {
                render_skybox(gc);
            }

            render_forward(gc);
        }

        if (!cameras.empty())
        {
            debug_line_renderer.render(gc, cameras[0]);
        }
    }

    void Renderer::load_shaders(GraphicContext& gc)
    {
        if (forward_shader)
        {
            return;
        }

        forward_shader = gc.compile({
            .vertex   = load_glsl_resource(IDR_GLSL_FORWARD_VERT),
            .fragment = load_glsl_resource(IDR_GLSL_FORWARD_FRAG),
        });

        skybox_shader = gc.compile({
            .vertex   = load_glsl_resource(IDR_GLSL_SKYBOX_VERT),
            .fragment = load_glsl_resource(IDR_GLSL_SKYBOX_FRAG),
        });

        cubemap_generator_shader = gc.compile({
            .vertex   = load_glsl_resource(IDR_GLSL_GENERATE_CUBEMAP_VERT),
            .fragment = load_glsl_resource(IDR_GLSL_GENERATE_CUBEMAP_FRAG),
        });

        cubemap_diffuse_filter_shader = gc.compile({
            .vertex   = load_glsl_resource(IDR_GLSL_GENERATE_CUBEMAP_VERT),
            .fragment = load_glsl_resource(IDR_GLSL_FILTER_CUBEMAP_DIFFUSE_FRAG),
        });

        cubemap_specular_filter_shader = gc.compile({
            .vertex   = load_glsl_resource(IDR_GLSL_GENERATE_CUBEMAP_VERT),
            .fragment = load_glsl_resource(IDR_GLSL_FILTER_CUBEMAP_SPECULAR_FRAG),
        });
    }

    void apply_camera(GraphicContext& gc, const Camera* camera)
    {
        check(camera);
        gc.set_uniform(std::to_underlying(UniformLocation::PROJECTION_MATRIX), camera->get_projection_matrix());
        gc.set_uniform(std::to_underlying(UniformLocation::VIEW_MATRIX),       camera->get_view_matrix());
    }

    auto generate_cubemap(pkzo::GraphicContext& gc, const std::shared_ptr<Shader>& shader, const pkzo::TextureOrCubeMap& texture, unsigned int mips = 1u)
    {
        constexpr auto TEXTURE0_SLOT = 0;

        return gc.generate_cubemap({
            .size      = 1024,
            .data_type = pkzo::DataType::FLOAT,
            .shader    = shader,
            .uniforms  = {
                {std::to_underlying(UniformLocation::TEXTURE), TEXTURE0_SLOT}
            },
            .textures  = {
                {TEXTURE0_SLOT, texture}
            },
            .miplevels = mips
        });
    }

    Renderer::IblMaps Renderer::genrate_ibl_maps(GraphicContext& gc, const std::shared_ptr<CubeMap>& light_probe)
    {
        constexpr auto MIPS = 7;
        check(light_probe);

        auto i = ibl_cache.find(light_probe);
        if (i != end(ibl_cache))
        {
            return i->second;
        }

        auto diffuse  = generate_cubemap(gc, cubemap_diffuse_filter_shader, light_probe);
        auto specular = generate_cubemap(gc, cubemap_specular_filter_shader, light_probe, MIPS);

        ibl_cache.try_emplace(light_probe, diffuse, specular);

        return {diffuse, specular};
    }

    int uniform_location_offset(UniformLocation base, int offset)
    {
        return static_cast<int>(base) + offset;
    }

    void Renderer::apply_light(GraphicContext& gc, int i, const Light* light)
    {
        check(i < MAX_LIGHTS);

        constexpr auto LIGHT_COMPONENTS = 5;
        if (light)
        {
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_TYPE,      i * LIGHT_COMPONENTS),  std::to_underlying(light->get_type()));
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_COLOR,     i * LIGHT_COMPONENTS),  light->get_color());
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_DIRECTION, i * LIGHT_COMPONENTS),  light->get_direction());
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_POSITION,  i * LIGHT_COMPONENTS),  light->get_position());
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_ANGLES,    i * LIGHT_COMPONENTS),  light->get_angles());
        }
        else
        {
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT0_TYPE, i * LIGHT_COMPONENTS),   std::to_underlying(LightType::NONE));
        }
    }

    void Renderer::apply_light_probe(GraphicContext& gc, int i, const std::shared_ptr<CubeMap>& probe)
    {
        check(i < MAX_LIGHT_PROBES);

        constexpr auto LIGHT_PROBE_COMPONENTS = 4;
        constexpr auto LIGHT_PROBE_SLOTS      = 3;
        constexpr auto LIGHT_ENVIRONMENT_SLOT = 4;
        constexpr auto LIGHT_DIFFUSE_SLOT     = 5;
        constexpr auto LIGHT_SPECULAR_SLOT    = 6;
        if (probe)
        {
            auto maps = genrate_ibl_maps(gc, probe);

            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT_PROBE0_ENABLED,     i * LIGHT_PROBE_COMPONENTS), 1);
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT_PROBE0_ENVIRONMENT, i * LIGHT_PROBE_COMPONENTS), LIGHT_ENVIRONMENT_SLOT + i * LIGHT_PROBE_SLOTS);
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT_PROBE0_DIFFUSE,     i * LIGHT_PROBE_COMPONENTS), LIGHT_DIFFUSE_SLOT     + i * LIGHT_PROBE_SLOTS);
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT_PROBE0_SPECULAR,    i * LIGHT_PROBE_COMPONENTS), LIGHT_SPECULAR_SLOT    + i * LIGHT_PROBE_SLOTS);

            gc.bind_texture(LIGHT_ENVIRONMENT_SLOT, probe);
            gc.bind_texture(LIGHT_DIFFUSE_SLOT,     maps.diffuse);
            gc.bind_texture(LIGHT_SPECULAR_SLOT,    maps.specular);
        }
        else
        {
            gc.set_uniform(uniform_location_offset(UniformLocation::LIGHT_PROBE0_ENABLED, i* LIGHT_PROBE_COMPONENTS), 0);
        }
    }

    void Renderer::apply_material(GraphicContext& gc, const std::shared_ptr<Material>& material)
    {
        constexpr auto BASE_COLOR_SLOT          = 0;
        constexpr auto METALLIC_ROUGHNESS_SLOT  = 1;
        constexpr auto NORMAL_SLOT              = 2;
        constexpr auto EMISSIVE_SLOT            = 3;

        check(material);

        gc.set_uniform(std::to_underlying(UniformLocation::BASE_COLOR_FACTOR),      glm::vec4(material->get_base_color_factor(), material->get_opacity_factor()));
        gc.set_uniform(std::to_underlying(UniformLocation::BASE_COLOR_MAP),         BASE_COLOR_SLOT);
        gc.set_uniform(std::to_underlying(UniformLocation::METALLIC_FACTOR),        material->get_metallic_factor());
        gc.set_uniform(std::to_underlying(UniformLocation::ROUGHNESS_FACTOR),       material->get_roughness_factor());
        gc.set_uniform(std::to_underlying(UniformLocation::METALLIC_ROUGHNESS_MAP), METALLIC_ROUGHNESS_SLOT);
        gc.set_uniform(std::to_underlying(UniformLocation::NORMAL_MAP),             NORMAL_SLOT);
        gc.set_uniform(std::to_underlying(UniformLocation::EMISSIVE_FACTOR),        material->get_emissive_factor());
        gc.set_uniform(std::to_underlying(UniformLocation::EMISSIVE_MAP),           EMISSIVE_SLOT);

        gc.bind_texture(BASE_COLOR_SLOT,         material->get_base_color_map());
        gc.bind_texture(METALLIC_ROUGHNESS_SLOT, material->get_metallic_roughness_map());
        gc.bind_texture(NORMAL_SLOT,             material->get_normal_map(), pkzo::FallbackTexture::NORMAL);
        gc.bind_texture(EMISSIVE_SLOT,           material->get_emissive_map());
    }

    void Renderer::render_skybox(pkzo::GraphicContext& gc)
    {
        constexpr auto SKYBOX_SLOT = 0;

        check(!skyboxes.empty());
        auto skybox = skyboxes[0];

        if (skybox->get_cubemap() == nullptr)
        {
            auto cubemap = generate_cubemap(gc, cubemap_generator_shader, skybox->get_texture());
            skybox->set_cubemap(cubemap);
        }

        gc.start_pass("Skybox", skybox_shader);
        gc.set_blend_mode(pkzo::BlendMode::DISABLED);
        gc.set_depth_test(pkzo::DepthTest::DISABLED);

        apply_camera(gc, cameras.at(0));

        gc.set_uniform(std::to_underlying(UniformLocation::ENVIRONMENT), SKYBOX_SLOT);

        gc.bind_texture(SKYBOX_SLOT, skybox->get_cubemap());

        gc.draw_fullscreen();

        gc.end_pass();

    }

    void Renderer::render_forward(pkzo::GraphicContext& gc)
    {
        gc.start_pass("Forward", forward_shader);
        gc.set_blend_mode(pkzo::BlendMode::ALPHA);
        gc.set_depth_test(pkzo::DepthTest::ENABLED);

        apply_camera(gc, cameras.at(0));

        for (auto i = 0u; i < MAX_LIGHT_PROBES; i++)
        {
            auto skybox = i < skyboxes.size() ? skyboxes[i] : nullptr;
            apply_light_probe(gc, i, skybox->get_cubemap());
        }

        // TODO select the most relevant lights.
        for (unsigned int i = 0u; i < MAX_LIGHTS; i++)
        {
            auto light = i < lights.size() ? lights[i] : nullptr;
            apply_light(gc, i, light);
        }

        for (const auto* geometry : geometries)
        {
            gc.set_uniform(std::to_underlying(UniformLocation::MODEL_MATRIX),  geometry->get_global_transform());
            apply_material(gc, geometry->get_material());
            gc.draw(geometry->get_mesh());
        }

        gc.end_pass();
    }

    void Renderer::LineRenderer::add_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color)
    {
        line_vertexes.push_back(start);
        line_vertexes.push_back(end);

        line_colors.push_back(start_color);
        line_colors.push_back(end_color);

        line_indexes.push_back({line_indexes.size() * 2u, line_indexes.size() * 2u + 1u});
    }

    void Renderer::LineRenderer::render(GraphicContext& gc, const Camera* camera)
    {
        if (line_vertexes.empty())
        {
            return;
        }

        if (line_vertex_buffer == nullptr)
        {
            line_vertex_buffer = gc.upload_mesh({
                .vertexes = std::move(line_vertexes),
                .colors   = std::move(line_colors),
                .lines    = std::move(line_indexes)
            }, true);
            check(line_vertex_buffer);
        }
        else
        {
            line_vertex_buffer->update({
                .vertexes = std::move(line_vertexes),
                .colors   = std::move(line_colors),
                .lines    = std::move(line_indexes)
            });
        }

        line_vertexes.clear();
        line_colors.clear();
        line_indexes.clear();

        if (line_shader == nullptr)
        {
            line_shader = gc.compile({
                .vertex   = load_glsl_resource(IDR_GLSL_DEBUG_LINE_VERT),
                .fragment = load_glsl_resource(IDR_GLSL_DEBUG_LINE_FRAG),
            });
            check(line_shader);
        }

        gc.start_pass("Debug Lines", line_shader);
        gc.set_blend_mode(pkzo::BlendMode::ALPHA);
        gc.set_depth_test(pkzo::DepthTest::DISABLED);

        apply_camera(gc, camera);

        gc.draw(line_vertex_buffer);

        gc.end_pass();
    }
}
