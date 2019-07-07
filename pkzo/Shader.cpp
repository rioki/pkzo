// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Shader.h"

#include <array>
#include <map>
#include <sstream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "dbg.h"
#include "stdex.h"
#include "Texture.h"

namespace pkzo
{
    constexpr auto MAX_LOG_MESSAGE = 256;

    Shader::Shader(const fs::path& file)
    {
        code = stdex::read_file(file);
    }

    Shader::~Shader()
    {
        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
            PKZO_SOFT_ASSERT(glGetError() == GL_NO_ERROR);
        }
    }

    void Shader::set_code(const std::string& value)
    {
        PKZO_ASSERT(program_id == 0);
        code = value;
    }

    const std::string& Shader::get_code()
    {
        return code;
    }

    void Shader::bind()
    {
        if (program_id == 0)
        {
            compile();
        }

        PKZO_ASSERT(program_id != 0);
        glUseProgram(program_id);
        bound = true;
        texture_slot = 0u;
    }

    void Shader::unbind()
    {
        PKZO_ASSERT(bound == true);
        glUseProgram(0);
        bound = false;
    }

    void Shader::set_uniform(const std::string_view id, const UniformValue& value)
    {
        PKZO_ASSERT(bound == true);

        int location = glGetUniformLocation(program_id, id.data());
        if (location != -1)
        {
            std::visit(stdex::overloaded {
            [&] (bool v) { glUniform1i(location, v); },
            [&] (int v) { glUniform1i(location, v); },
            [&] (glm::uint v) { glUniform1i(location, v); },
            [&] (float v) { glUniform1f(location, v); },
            [&] (const glm::ivec2 v) { glUniform2i(location, v.x, v.y); },
            [&] (const glm::uvec2 v) { glUniform2i(location, v.x, v.y); },
            [&] (const glm::vec2 v) { glUniform2f(location, v.x, v.y); },
            [&] (const glm::ivec3 v) { glUniform3i(location, v.x, v.y, v.z); },
            [&] (const glm::uvec3 v) { glUniform3i(location, v.x, v.y, v.z); },
            [&] (const glm::vec3 v) { glUniform3f(location, v.x, v.y, v.z); },
            [&] (const glm::ivec4 v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
            [&] (const glm::uvec4 v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
            [&] (const glm::vec4 v) { glUniform4f(location, v.x, v.y, v.z, v.w); },
            [&] (const glm::mat2 v) { glUniformMatrix2fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
            [&] (const glm::mat3 v) { glUniformMatrix3fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
            [&] (const glm::mat4 v) { glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
            }, value);
        }
    }

    void Shader::set_texture(const std::string_view id, const std::shared_ptr<Texture>& value)
    {
        PKZO_ASSERT(bound);
        if (value == nullptr)
        {
            PKZO_THROW(std::invalid_argument, "Texture value is null.");
        }
        value->bind(texture_slot);
        set_uniform(id, texture_slot);
        texture_slot++;
    }

    unsigned int Shader::get_attribute(const std::string_view name)
    {
        PKZO_ASSERT(bound);

        unsigned int id = glGetAttribLocation(program_id, name.data());
        PKZO_ASSERT(glGetError() == GL_NO_ERROR);

        return id;
    }

    void Shader::bind_output(const std::string_view name, unsigned int channel)
    {
        PKZO_ASSERT(bound);
        glBindFragDataLocation(program_id, channel, name.data());
        PKZO_ASSERT(glGetError() == GL_NO_ERROR);
    }

    std::string create_preamble(const std::map<std::string, std::string> macros)
    {
        std::stringstream buff;
        buff << "#version 430" << std::endl;
        for (auto [id, value] : macros)
        {
            buff << "#define " << id << " " << value << std::endl;
        }
        return buff.str();
    }

    glm::uint compile_source(GLenum type, const std::map<std::string, std::string>& macros, const std::string& code)
    {
        auto preamble = create_preamble(macros);
        auto shader_id = glCreateShader(type);

        auto sources = std::array<const GLchar *, 2>{preamble.data(), code.data()};
        auto sources_lengths = std::array<GLint, 2>{static_cast<GLint>(preamble.size()), static_cast<GLint>(code.size())};
        glShaderSource(shader_id, 2, sources.data(), sources_lengths.data());
        glCompileShader(shader_id);

        auto logstr = std::string(MAX_LOG_MESSAGE, '\0');
        glGetShaderInfoLog(shader_id, static_cast<GLint>(logstr.size()), NULL, logstr.data());

        auto status = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(shader_id);
            throw std::runtime_error(logstr);
        }

        return shader_id;
    }

    glm::uint link_program(const std::vector<glm::uint>& shader_ids)
    {
        auto program_id = glCreateProgram();
        for (auto shader_id : shader_ids)
        {
            glAttachShader(program_id, shader_id);
            PKZO_ASSERT(glGetError() == GL_NO_ERROR);
        }

        glLinkProgram(program_id);

        auto logstr = std::string(MAX_LOG_MESSAGE, '\0');
        glGetProgramInfoLog(program_id, static_cast<GLint>(logstr.size()), NULL, logstr.data());

        auto status = 0;
        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        if (!status)
        {
            glDeleteProgram(program_id);
            throw std::runtime_error(logstr);
        }

        return program_id;
    }

    void Shader::compile()
    {
        PKZO_ASSERT(program_id == 0);

        auto vertex_id = 0u;
        auto fragment_id = 0u;
        try
        {
            auto vertex_macros = std::map<std::string, std::string>{{"PKZO_VERTEX_CODE", "1"}};
            vertex_id = compile_source(GL_VERTEX_SHADER, vertex_macros, code);

            auto fragment_macros = std::map<std::string, std::string>{{"PKZO_FRAGMENT_CODE", "1"}};
            fragment_id = compile_source(GL_FRAGMENT_SHADER, fragment_macros, code);

            program_id = link_program({vertex_id, fragment_id});

            // NOTE: glDeleteShader() actually does not delete the shader, it only
            // flags the shader for deletion. The shaders will be deleted when
            // the program gets deleted.
            glDeleteShader(vertex_id);
            glDeleteShader(fragment_id);
            PKZO_ASSERT(glGetError() == GL_NO_ERROR);
        }
        catch (...)
        {
            if (vertex_id != 0)
            {
                glDeleteShader(vertex_id);
            }
            if (fragment_id != 0)
            {
                glDeleteShader(fragment_id);
            }
            if (program_id != 0)
            {
                glDeleteProgram(program_id);
            }
        }

    }
}
