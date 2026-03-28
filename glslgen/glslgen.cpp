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

#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <tinyformat.h>

#include <pkzo/stdng.h>
#include <pkzo/Shader.h>
#include <pkzo/OpenGLMesh.h>

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
struct AttribSpec
{
    pkzo::AttributeLocation location;
    std::string             type;
    std::string             id;
};
const auto attributes = std::vector<AttribSpec>{
    {pkzo::AttributeLocation::VERTEX,   "vec3", "atr_Vertex"},
    {pkzo::AttributeLocation::TEXCOORD, "vec2", "atr_TexCoord"}
};

struct UniformSpec
{
    pkzo::UniformLocation location;
    std::string     type;
    std::string     id;
    unsigned int    size = 0; // 0 == scalar
};
const auto uniforms = std::vector<UniformSpec>{
    // Tansforms
    {pkzo::UniformLocation::PROJECTION_MATRIX, "mat4",         "uni_ProjectionMatrix"},
    {pkzo::UniformLocation::VIEW_MATRIX,       "mat4",         "uni_ViewMatrix"},
    {pkzo::UniformLocation::MODEL_MATRIX,      "mat4",         "uni_ModelMatrix"},
    {pkzo::UniformLocation::COLOR_FACTOR,      "vec4",         "uni_ColorFactor"},
    {pkzo::UniformLocation::COLOR_MAP,         "sampler2D",    "uni_ColorMap"},
};


void write_file(const std::filesystem::path& filename, const std::string& contents)
{
    auto output = std::ofstream(filename);
    output << contents;
}

void make_attribute_glsl(const std::filesystem::path& filename)
{
    auto output = std::ofstream(filename);

    output << legal;

    for (const auto& attribute : attributes)
    {
        output << tfm::format("layout(location = %d) in %s %s;\n", std::to_underlying(attribute.location), attribute.type, attribute.id);
    }
}

void make_uniforms_glsl(const std::filesystem::path& filename)
{
    auto output = std::ofstream(filename);

    output << legal;

    for (const auto& uniform : uniforms)
    {
        if (uniform.size == 0)
        {
            output << tfm::format("layout(location = %d) uniform %s %s;\n", std::to_underlying(uniform.location), uniform.type, uniform.id);
        }
        else
        {
            output << tfm::format("layout(location = %d) uniform %s %s[%d];\n", std::to_underlying(uniform.location), uniform.type, uniform.id, uniform.size);
        }
    }
}

void make_outputs_glsl(const std::filesystem::path& filename)
{
    auto output = std::ofstream(filename);

    output << legal;

    for (auto i = 0u; i < 8u; i++)
    {
        output << tfm::format("layout(location = %d) out vec4 out_FragColor%d;\n", i, i);
    }
}

int main(int argc, const char* argv[])
{
    try
    {
        if (argc != 2)
        {
            tfm::printf("Please specify the file to generate.");
            return EXIT_FAILURE;
        }

        auto path = std::filesystem::path(argv[1]);
        auto filename = path.filename().string();
        switch (stdng::hash(filename))
        {
            case stdng::hash("attributes.glsl"):
                tfm::printf("Generating %s", filename);
                make_attribute_glsl(path);
                break;
            case stdng::hash("uniforms.glsl"):
                tfm::printf("Generating %s", filename);
                make_uniforms_glsl(path);
                break;
            case stdng::hash("outputs.glsl"):
                tfm::printf("Generating %s", filename);
                make_outputs_glsl(path);
                break;
            default:
                tfm::printf("Unknown GLSL source %s", filename);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex)
    {
        tfm::printf("Unexpected error: %s", ex.what());
        return EXIT_FAILURE;
    }
}
