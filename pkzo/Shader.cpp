// GLint id;
// glGetIntegerv(GL_CURRENT_PROGRAM,&id);//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Shader.h"

#include "Texture.h"

namespace pkzo
{
    auto get_bound_shader() noexcept
    {
        GLint id = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);
        return id;
    }

    Shader::Shader(const std::string& vc, const std::string& fc)
    : vertex_code(vc), fragment_code(fc) {}

    Shader::~Shader()
    {
        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
            assert(glGetError() == GL_NO_ERROR);
        }
    }

    bool Shader::compile()
    {
        assert(program_id == 0);

        int status = 0;
        char logstr[256];

        const GLchar* vbuff[1] = { vertex_code.c_str() };

        unsigned int vertex_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_id, 1, vbuff, NULL);
        glCompileShader(vertex_id);

        glGetShaderInfoLog(vertex_id, 256, NULL, logstr);

        glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            throw std::runtime_error(logstr);
        }

        const GLchar* fbuff[1] = { fragment_code.c_str() };

        unsigned int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_id, 1, fbuff, NULL);
        glCompileShader(fragment_id);

        glGetShaderInfoLog(fragment_id, 256, NULL, logstr);

        glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            throw std::runtime_error(logstr);
        }

        assert(glGetError() == GL_NO_ERROR);

        program_id = glCreateProgram();
        glAttachShader(program_id, vertex_id);
        assert(glGetError() == GL_NO_ERROR);
        glAttachShader(program_id, fragment_id);
        assert(glGetError() == GL_NO_ERROR);
        glLinkProgram(program_id);

        glGetProgramInfoLog(program_id, 256, NULL, logstr);

        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        if (!status)
        {
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            glDeleteProgram(program_id);
            throw std::runtime_error(logstr);
        }

        // NOTE: glDeleteShader() actually does not delete the shader, it only
        // flags the shader for deletion. The shaders will be deleted when
        // the program gets deleted.
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);

        assert(glGetError() == GL_NO_ERROR);
    }

    void Shader::bind()
    {
        if (program_id == 0)
        {
            compile();
        }
        glUseProgram(program_id);
        assert(glGetError() == GL_NO_ERROR);
        texture_slot = 0u;
    }

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    void Shader::set_uniform(const std::string_view id, const UniformValue& value) noexcept
    {
        assert(get_bound_shader() == program_id);

        int location = glGetUniformLocation(program_id, id.data());
        if (location != -1)
        {
            std::visit(overloaded {
                [&] (bool v) { glUniform1i(location, v); },
                [&] (int v) { glUniform1i(location, v); },
                [&] (glm::uint v) { glUniform1i(location, v); },
                [&] (float v) { glUniform1f(location, v); },
                [&] (glm::ivec2 v) { glUniform2i(location, v.x, v.y); },
                [&] (glm::uvec2 v) { glUniform2i(location, v.x, v.y); },
                [&] (glm::vec2 v) { glUniform2f(location, v.x, v.y); },
                [&] (glm::ivec3 v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (glm::uvec3 v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (glm::vec3 v) { glUniform3f(location, v.x, v.y, v.z); },
                [&] (glm::ivec4 v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (glm::uvec4 v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (glm::vec4 v) { glUniform4f(location, v.x, v.y, v.z, v.w); },
                [&] (glm::mat2 v) { glUniformMatrix2fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (glm::mat3 v) { glUniformMatrix3fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (glm::mat4 v) { glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
            }, value);
        }
        assert(glGetError() == GL_NO_ERROR);
    }

    void Shader::set_uniform(const std::string_view id, const std::shared_ptr<Texture>& value) noexcept
    {
        assert(get_bound_shader() == program_id);
        if (value == nullptr)
        {
            throw std::invalid_argument("Texture value is null.");
        }
        value->bind(texture_slot);
        set_uniform(id, texture_slot);
        texture_slot++;
    }

    unsigned int Shader::get_attribute(const std::string& name) noexcept
    {
        assert(get_bound_shader() == program_id);
        unsigned int id = glGetAttribLocation(program_id, name.c_str());
        assert(glGetError() == GL_NO_ERROR);
        return id;
    }

    void Shader::bind_output(const std::string& name, unsigned int channel) noexcept
    {
        assert(get_bound_shader() == program_id);
        glBindFragDataLocation(program_id, channel, name.c_str());
        assert(glGetError() == GL_NO_ERROR);
    }
}
