// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "Shader.h"

#include <array>
#include <fstream>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"
#include "opengl.h"
#include "strconv.h"
#include "utils.h"

namespace pkzo
{
    using opengl::check_glerror;

    constexpr auto CODE_PREFIX =
        "#version 430\n"
        "#define PKZO_VERSION 10\n"; // 0.1.0

    constexpr auto VERTEX_PREFIX =
        "#define PKZO_VERTEX\n"
        "\n"
        "uniform mat4 pkzo_ProjectionMatrix;\n"
        "uniform mat4 pkzo_ViewMatrix;\n"
        "uniform mat4 pkzo_ModelMatrix;\n"
        "\n"
        "layout(location = 0) in vec3 pkzo_Vertex;\n"
        "layout(location = 1) in vec3 pkzo_Normal;\n"
        "layout(location = 2) in vec3 pkzo_Tangent;\n"
        "layout(location = 3) in vec2 pkzo_TexCoord;\n";

    constexpr auto FRAGMENT_PREFIX =
        "#define PKZO_FRAGMENT\n"
        "\n"
        "out vec4 pkzo_FragColor;\n";

    std::shared_ptr<Shader> Shader::load_file(const std::filesystem::path& file)
    {
        return std::make_shared<Shader>(file);
    }

    Shader::Shader(const std::filesystem::path& file)
    : Shader(load_text_file(file)) {}

    Shader::Shader(const std::string& _code)
    : code(_code) {}

    Shader::~Shader() = default;

    void Shader::set_code(const std::string& value) noexcept
    {
        code = value;
    }

    const std::string& Shader::get_code() const noexcept
    {
        return code;
    }

    void Shader::compile()
    {
        std::stringstream log;
        try
        {
            compile(log);
        }
        catch (...)
        {
            trace(log.str());
            throw;
        }
        trace(log.str());
    }

    void Shader::compile(std::ostream& log)
    {
        auto tmp = std::make_unique<opengl::Shader>();

        tmp->compile(opengl::ShaderType::VERTEX_SHADER,   {CODE_PREFIX, VERTEX_PREFIX,   code.data()}, log);
        tmp->compile(opengl::ShaderType::FRAGMENT_SHADER, {CODE_PREFIX, FRAGMENT_PREFIX, code.data()}, log);
        tmp->link(log);

        shader = std::move(tmp);
    }

    bool Shader::is_compiled() const noexcept
    {
        return shader != nullptr;
    }

    void Shader::bind()
    {
        if (!is_compiled())
        {
            compile();
        }

        shader->bind();
    }

    void Shader::set_uniform(const std::string_view name, const UniformValue& value) noexcept
    {
        check(shader != nullptr);
        shader->set_uniform(name, value);
    }
}

