// OpenGL Object Wrapper
// Copyright 2016-2023 Sean Farrell <sean.farrell@rioki.org>
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
#include "Shader.h"

#include "glow.h"

namespace std
{
    std::ostream& operator << (std::ostream& os, const glow::UniformValue& value)
    {
        std::visit(rex::overloaded {
            [&] (bool v)              { os << v; },
            [&] (int v)               { os << v; },
            [&] (unsigned int v)      { os << v; },
            [&] (float v)             { os << v; },
            [&] (const glm::ivec2& v) { os << v; },
            [&] (const glm::uvec2& v) { os << v; },
            [&] (const glm::vec2& v)  { os << v; },
            [&] (const glm::ivec3& v) { os << v; },
            [&] (const glm::uvec3& v) { os << v; },
            [&] (const glm::vec3& v)  { os << v; },
            [&] (const glm::ivec4& v) { os << v; },
            [&] (const glm::uvec4& v) { os << v; },
            [&] (const glm::vec4& v)  { os << v; },
            [&] (const glm::mat2& v)  { os << v; },
            [&] (const glm::mat3& v)  { os << v; },
            [&] (const glm::mat4& v)  { os << v; }
        }, value);

        return os;
    }
}

namespace glow
{
    Shader::Shader(const std::string& l) noexcept
    : label(l) {};

    Shader::~Shader()
    {
        if (!shader_ids.empty())
        {
            for (const auto shader_id : shader_ids)
            {
                 glDeleteShader(shader_id);
            }
            GLOW_CHECK_ERROR();
        }

        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
            GLOW_CHECK_ERROR();
        }
    }

    void Shader::compile(ShaderType type, const std::string_view code, std::ostream& log)
    {
        auto status = 0;
        auto logstr = std::array<char, 256>();

        auto code_ptrs = std::array<const char*, 1>{code.data()};

        unsigned int shader_id = glCreateShader(rex::to_underlying(type));
        glShaderSource(shader_id, static_cast<GLsizei>(code_ptrs.size()), code_ptrs.data(), nullptr);
        glCompileShader(shader_id);

        glGetShaderInfoLog(shader_id, static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(shader_id);
            throw std::runtime_error("Failed to compile shader.");
        }

        GLOW_CHECK_ERROR();
        shader_ids.push_back(shader_id);
    }

    void Shader::compile(ShaderType type, const std::string_view code)
    {
        std::stringstream log;
        try
        {
            compile(type, code, log);
        }
        catch (...)
        {
            trace(log.str());
            throw;
        }

        if (!log.str().empty())
        {
            trace(log.str());
        }
    }

    void Shader::link(std::ostream& log)
    {
        check(program_id == 0);
        check(shader_ids.size() != 0);

        auto status = 0;
        auto logstr = std::array<char, 256>();

        program_id = glCreateProgram();
        for (const auto shader_id : shader_ids)
        {
             glAttachShader(program_id, shader_id);
        }
        glLinkProgram(program_id);
        GLOW_CHECK_ERROR();

        glGetProgramInfoLog(program_id,  static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        if (!status)
        {
            throw std::runtime_error("Failed to link shader program.");
        }

        // NOTE: glDeleteShader() actually does not delete the shader, it only
        // flags the shader for deletion. The shaders will be deleted when
        // the program gets deleted.
        for (const auto shader_id : shader_ids)
        {
            glDeleteShader(shader_id);
        }
        GLOW_CHECK_ERROR();
        shader_ids.clear();

        glObjectLabel(GL_PROGRAM, program_id, static_cast<GLsizei>(label.size()), label.data());
        GLOW_CHECK_ERROR();
    }

    void Shader::link()
{
        std::stringstream log;
        try
        {
            link(log);
        }
        catch (...)
        {
            trace(log.str());
            throw;
        }

        if (!log.str().empty())
        {
            trace(log.str());
        }
    }

    void Shader::bind() noexcept
    {
        check(program_id != 0);
        glUseProgram(program_id);
        GLOW_CHECK_ERROR();
    }

    void Shader::set_uniform(const std::string_view name, const UniformValue& value) noexcept
    {
        check(program_id != 0);
        auto location = glGetUniformLocation(program_id, name.data());
        if (location != -1)
        {
            std::visit(rex::overloaded {
                [&] (bool v)              { glUniform1i(location, v); },
                [&] (int v)               { glUniform1i(location, v); },
                [&] (unsigned int v)      { glUniform1i(location, v); },
                [&] (float v)             { glUniform1f(location, v); },
                [&] (const glm::ivec2& v) { glUniform2i(location, v.x, v.y); },
                [&] (const glm::uvec2& v) { glUniform2i(location, v.x, v.y); },
                [&] (const glm::vec2& v)  { glUniform2f(location, v.x, v.y); },
                [&] (const glm::ivec3& v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (const glm::uvec3& v) { glUniform3i(location, v.x, v.y, v.z); },
                [&] (const glm::vec3& v)  { glUniform3f(location, v.x, v.y, v.z); },
                [&] (const glm::ivec4& v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (const glm::uvec4& v) { glUniform4i(location, v.x, v.y, v.z, v.w); },
                [&] (const glm::vec4& v)  { glUniform4f(location, v.x, v.y, v.z, v.w); },
                [&] (const glm::mat2& v)  { glUniformMatrix2fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const glm::mat3& v)  { glUniformMatrix3fv(location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const glm::mat4& v)  { glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(v)); }
            }, value);
        }
        GLOW_CHECK_ERROR();
    }

    void Shader::set_uniform(const std::string_view name, Texture& texture) noexcept
    {
        auto slot = get_texture_slot(name);
        texture.bind(slot);
        set_uniform(name, slot);
    }

    unsigned Shader::get_texture_slot(const std::string_view name) noexcept
    {
        if (auto i = texture_slots.find(name); i != end(texture_slots))
        {
            return std::get<unsigned int>(*i);
        }

        auto slot = last_texture_slot;
        texture_slots[std::string{name}] = slot;
        last_texture_slot++;

        return slot;
    }

    unsigned int Shader::get_attribute(const std::string_view name) noexcept
    {
        auto loc = glGetAttribLocation(program_id, name.data());
        GLOW_CHECK_ERROR();
        return loc;
    }

    void Shader::bind_output(const std::string_view name, unsigned int location) noexcept
    {
        glBindFragDataLocation(program_id, location, name.data());
        GLOW_CHECK_ERROR();
    }
}
