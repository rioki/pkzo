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

#include "pch.h"

#include "OpenGLShader.h"

#include <stdexcept>
#include <map>

#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

namespace pkzo
{
    std::string glShaderInfoLogEx(GLuint shader)
    {
        auto length = GLint{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        if (length > 0)
        {
            auto log = std::string(length, '\0');
            glGetShaderInfoLog(shader, length, nullptr, log.data());
            return log;
        }
        return {};
    }

    std::string glGetProgramInfoLogEx(GLuint program)
    {
        auto length = GLint{0};
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        if (length > 0)
        {
            auto log = std::string(length, '\0');
            glGetProgramInfoLog(program, length, nullptr, log.data());
            return log;
        }
        return {};
    }

    enum class ShaderType : GLenum
    {
        COMPUTE         = GL_COMPUTE_SHADER,
        VERTEX          = GL_VERTEX_SHADER,
        TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
        GEOMETRY        = GL_GEOMETRY_SHADER,
        FRAGMENT        = GL_FRAGMENT_SHADER
    };

    class ShaderStage
    {
    public:
        ShaderStage() = default;

        ShaderStage(ShaderType type)
        {
            handle = glCreateShader(std::to_underlying(type));
        }

        ShaderStage(ShaderStage&& rhs) noexcept
        : handle(std::exchange(rhs.handle, 0u)) {}

        ~ShaderStage()
        {
            if (handle != 0u)
            {
                glDeleteShader(handle);
            }
        }

        ShaderStage& operator = (ShaderStage&& rhs) noexcept
        {
            if (this != &rhs)
            {
                release();
                handle = std::exchange(rhs.handle, 0u);
            }
            return *this;
        }

        operator GLuint () const
        {
            return handle;
        }

        bool compile(const std::vector<const char*>& code)
        {
            glShaderSource(handle, static_cast<GLsizei>(code.size()), code.data(), nullptr);
            glCompileShader(handle);

            auto info_log = glShaderInfoLogEx(handle);
            if (info_log.empty() == false)
            {
                trace(info_log);
            }

            auto success = GLint{0};
            glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
            return success;
        }

        GLuint release()
        {
            auto t = handle;
            handle = 0u;
            return t;
        }

    private:
        GLuint handle = 0u;

        ShaderStage(const ShaderStage&) = delete;
        ShaderStage& operator = (const ShaderStage&) = delete;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram()
        {
            handle = glCreateProgram();
        }

        ShaderProgram(ShaderProgram&& rhs) noexcept
        : handle(std::exchange(rhs.handle, 0u)) {}

        ~ShaderProgram()
        {
            if (handle != 0u)
            {
                glDeleteProgram(handle);
            }
        }

        ShaderProgram& operator = (ShaderProgram&& rhs) noexcept
        {
            if (this != &rhs)
            {
                release();
                handle = std::exchange(rhs.handle, 0u);
            }
            return *this;
        }

        bool link(const std::vector<ShaderStage>& stages)
        {
            for (const auto& stage : stages)
            {
                glAttachShader(handle, stage);
            }

            glLinkProgram(handle);

            auto info_log = glGetProgramInfoLogEx(handle);
            if (info_log.empty() == false)
            {
                trace(info_log);
            }

            auto success = GLint{0};
            glGetProgramiv(handle, GL_LINK_STATUS, &success);

            for (const auto& stage : stages)
            {
                glDetachShader(handle, stage);
            }

            return success;
        }

        GLuint release()
        {
            auto t = handle;
            handle = 0u;
            return t;
        }

    private:
        GLuint handle = 0u;

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator = (const ShaderProgram&) = delete;
    };

    GLuint compile(const std::map<ShaderType, std::string>& code)
    {
        auto stages = std::vector<ShaderStage>();
        stages.reserve(code.size());

        for (const auto [type, source] : code)
        {
            auto stage = ShaderStage(type);
            auto s = stage.compile({source.data()});
            if (s)
            {
                stages.push_back(std::move(stage));
            }
            else
            {
                throw std::runtime_error("Failed to compile shader");
            }
        }

        auto program = ShaderProgram();
        auto s = program.link(stages);

        if (s)
        {
            return program.release();
        }
        else
        {
            throw std::runtime_error("Failed to link shader");
        }
    }

    OpenGLShader::OpenGLShader(const Source& source)
    {
        handle = compile({
            {ShaderType::VERTEX,   source.vertex},
            {ShaderType::FRAGMENT, source.fragment}
        });
        assert(handle != 0u);
    }

    OpenGLShader::~OpenGLShader()
    {
        assert(handle != 0);
        glDeleteShader(handle);
    }

    void OpenGLShader::bind()
    {
        assert(handle != 0);
        glUseProgram(handle);
    }

    int OpenGLShader::get_uniform_location(const std::string_view name) const
    {
        assert(handle != 0);
        return glGetUniformLocation(handle, name.data());
    }

    int OpenGLShader::get_attribute_location(const std::string_view name) const
    {
        assert(handle != 0);
        return glGetAttribLocation(handle, name.data());
    }
}
