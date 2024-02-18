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

#pragma once

#include <variant>
#include <string>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "defines.h"
#include "Texture.h"

namespace glow
{
    //! Uniform value type.
    using UniformValue = std::variant<
        bool,
        unsigned int,
        int ,
        float,
        glm::ivec2,
        glm::uvec2,
        glm::vec2,
        glm::ivec3,
        glm::uvec3,
        glm::vec3,
        glm::ivec4,
        glm::uvec4,
        glm::vec4,
        glm::mat2,
        glm::mat3,
        glm::mat4>;

    enum class ShaderType : GLenum
    {
        COMPUTE         = GL_COMPUTE_SHADER,
        VERTEX          = GL_VERTEX_SHADER,
        TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
        GEOMETRY        = GL_GEOMETRY_SHADER,
        FRAGMENT        = GL_FRAGMENT_SHADER
    };

    class GLOW_EXPORT Shader
    {
    public:
        Shader(const std::string& label = "") noexcept;
        ~Shader();

        void compile(ShaderType type, const std::string_view code, std::ostream& log);
        void compile(ShaderType type, const std::string_view code);
        void link(std::ostream& log);
        void link();

        void bind() noexcept;

        void set_uniform(const std::string_view name, const UniformValue& value) noexcept;
        void set_uniform(const std::string_view name, Texture& texture) noexcept;
        unsigned get_texture_slot(const std::string_view name) noexcept;

        unsigned int get_attribute(const std::string_view name) noexcept;

        void bind_output(const std::string_view name, unsigned int location) noexcept;

    private:
        unsigned int              program_id = 0;
        std::vector<unsigned int> shader_ids;
        std::string               label;

        unsigned int last_texture_slot = 0u;
        std::map<std::string, unsigned int, std::less<>> texture_slots;

        Shader(const Shader&) = delete;
        Shader& operator = (const Shader&) = delete;
    };
}
