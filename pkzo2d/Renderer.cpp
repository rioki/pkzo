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

#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include <magic_enum/magic_enum.hpp>
#include <tinyformat.h>

#include "resources.h"
#include <pkzo/OpenGLMesh.h>
#include "Shape.h"

namespace pkzo2d
{
    using pkzo::AttributeLocation;

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

    enum class UniformLocation : int
    {
        PROJECTION_MATRIX,
        VIEW_MATRIX,
        MODEL_MATRIX,
        COLOR_FACTOR,
        COLOR_MAP
    };

    struct AttribSpec
    {
        pkzo::AttributeLocation location;
        std::string             type;
        std::string             id;
    };
    const auto attributes = std::vector<AttribSpec>{
        {AttributeLocation::VERTEX,   "vec3", "atr_Vertex"},
        {AttributeLocation::TEXCOORD, "vec2", "atr_TexCoord"}
    };

    struct UniformSpec
    {
        UniformLocation location;
        std::string     type;
        std::string     id;
        unsigned int    size = 0; // 0 == scalar
    };
    const auto uniforms = std::vector<UniformSpec>{
        // Tansforms
        {UniformLocation::PROJECTION_MATRIX, "mat4",         "uni_ProjectionMatrix"},
        {UniformLocation::VIEW_MATRIX,       "mat4",         "uni_ViewMatrix"},
        {UniformLocation::MODEL_MATRIX,      "mat4",         "uni_ModelMatrix"},
        {UniformLocation::COLOR_FACTOR,      "vec4",         "uni_ColorFactor"},
        {UniformLocation::COLOR_MAP,         "sampler2D",    "uni_ColorMap"},
    };

    #ifdef DEV_BUILD
    // DESIGN: Writing the include files from the lib is a bit nasty, but it does the trick.
    // Internally these files are not used, just for IDE's libter.
    void write_include_file(const std::string& filename, const std::string& contents)
    {
        auto inc_file = std::filesystem::path(SOLUTION_DIR) / "pkzo2d" / filename;
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

        for (auto i = 0u; i < 1u; i++)
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

    Renderer::Renderer(const glm::vec2& size)
    {
        auto hs = size * 0.5f;
        projection_matrix = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);
    }

    Renderer::~Renderer() = default;

    void Renderer::resize(const glm::vec2& size)
    {
        auto hs = size * 0.5f;
        projection_matrix = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);
    }

    void Renderer::add(Shape* shape)
    {
        shapes.push_back(shape);
    }

    void Renderer::remove(Shape* shape)
    {
        std::erase(shapes, shape);
    }

    void Renderer::render(pkzo::GraphicContext& gc)
    {
        if (shapes.empty())
        {
            return;
        }

        using enum UniformLocation;

        if (!screen_shader)
        {
            screen_shader = gc.compile({
                .vertex   = expand_includes(get_resource("Screen.vert")),
                .fragment = expand_includes(get_resource("Screen.frag")),
            });
        }

        gc.start_pass("Screen", screen_shader);
        gc.set_blend_mode(pkzo::BlendMode::ALPHA);
        gc.set_depth_test(pkzo::DepthTest::DISABLED);

        gc.set_uniform(std::to_underlying(PROJECTION_MATRIX), projection_matrix);
        gc.set_uniform(std::to_underlying(VIEW_MATRIX),       view_matrix);

        for (const auto* shape : shapes)
        {
            gc.set_uniform(std::to_underlying(MODEL_MATRIX), shape->get_model_matrix());

            gc.set_uniform(std::to_underlying(COLOR_FACTOR), shape->get_color());
            gc.set_uniform(std::to_underlying(COLOR_MAP),    0);

            gc.bind_texture(0, shape->get_texture());

            gc.draw(shape->get_mesh());
        }

        gc.end_pass();
    }
}
