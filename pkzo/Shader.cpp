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
#include "strconv.h"
#include "utils.h"

namespace pkzo
{
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
        "in vec3 pkzo_Vertex;\n"
        "in vec3 pkzo_Normal;\n"
        "in vec3 pkzo_Tangent;\n"
        "in vec2 pkzo_TexCoord;\n";

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

    Shader::~Shader()
    {
        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
            check_glerror();
        }
    }

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
        check(program_id == 0);

        auto status = 0;
        auto logstr = std::array<char, 256>();

        auto vbuff = std::array<const char*, 3>{CODE_PREFIX, VERTEX_PREFIX, code.data()};

        unsigned int vertex_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_id, static_cast<GLsizei>(vbuff.size()), vbuff.data(), nullptr);
        glCompileShader(vertex_id);

        glGetShaderInfoLog(vertex_id, static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            throw std::runtime_error("Failed to compile vertex shader.");
        }

        check_glerror();

        auto fbuff = std::array<const char*, 3>{CODE_PREFIX, FRAGMENT_PREFIX, code.data()};

        unsigned int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_id,  static_cast<GLsizei>(fbuff.size()), fbuff.data(), nullptr);
        glCompileShader(fragment_id);

        glGetShaderInfoLog(fragment_id, static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            throw std::runtime_error("Failed to compile fragment shader.");
        }

        check_glerror();

        program_id = glCreateProgram();
        glAttachShader(program_id, vertex_id);
        check(glGetError() == GL_NO_ERROR);
        glAttachShader(program_id, fragment_id);
        check(glGetError() == GL_NO_ERROR);
        glLinkProgram(program_id);

        glGetShaderInfoLog(vertex_id,  static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            glDeleteProgram(program_id);
            throw std::runtime_error("Failed to link shader program.");
        }

        // NOTE: glDeleteShader() actually does not delete the shader, it only
        // flags the shader for deletion. The shaders will be deleted when
        // the program gets deleted.
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);

        check_glerror();
    }

    bool Shader::is_compiled() const noexcept
    {
        return program_id != 0;
    }

    void Shader::bind()
    {
        if (!is_compiled())
        {
            compile();
        }

        check(program_id != 0);
        glUseProgram(program_id);
        check_glerror();
    }

    void Shader::set_uniform(const std::string_view name, const UniformValue& value) noexcept
    {
        check(program_id != 0);
        if (int location = glGetUniformLocation(program_id, name.data()); location != -1)
        {
            std::visit(overloaded {
                [&] (bool v)         { glUniform1i(location, v); },
                [&] (int v)          { glUniform1i(location, v); },
                [&] (uint v)         { glUniform1i(location, v); },
                [&] (float v)        { glUniform1f(location, v); },
                [&] (const ivec2& v) { glUniform2i(location, v.x, v.y); },
                [&] (const uvec2& v) { glUniform2i(location, v.x, v.y); },
                [&] (const vec2& v)  { glUniform2f(location, v.x, v.y); },
                [&] (const ivec3& v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (const uvec3& v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (const vec3& v)  { glUniform3f(location, v.x, v.y, v.z); },
                [&] (const ivec4& v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (const uvec4& v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (const vec4& v)  { glUniform4f(location, v.x, v.y, v.z, v.w); },
                [&] (const mat2& v)  { glUniformMatrix2fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const mat3& v)  { glUniformMatrix3fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const mat4& v)  { glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(v)); }
            }, value);
        }
        check_glerror();
    }

    int Shader::get_attribute(const std::string_view name) noexcept
    {
        check(program_id != 0);
        auto id = glGetAttribLocation(program_id, name.data());
        check_glerror();
        return id;
    }

    void Shader::bind_output(const std::string_view name, uint channel) noexcept
    {
        check(program_id != 0);
        glBindFragDataLocation(program_id, channel, name.data());
        check_glerror();
    }
}

