//
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

#ifndef _ICE_SHADER_H_
#define _ICE_SHADER_H_

#include "config.h"

#include <memory>
#include <string>
#include <variant>
#include <glm/glm.hpp>

namespace pkzo
{
    class Texture;

    using UniformValue = std::variant<bool, int, glm::uint, float,
        glm::ivec2, glm::uvec2, glm::vec2,
        glm::ivec3, glm::uvec3, glm::vec3,
        glm::ivec4, glm::uvec4, glm::vec4,
        glm::mat2, glm::mat3, glm::mat4>;

    class PKZO_EXPORT Shader
    {
    public:
        Shader(const std::string& vertex_code, const std::string& fragment_code);
        Shader(const Shader&) = delete;
        ~Shader();
        Shader& operator = (const Shader&) = delete;

        void compile();

        void bind();

        void set_uniform(const std::string_view id, const UniformValue& value) noexcept;

        void set_uniform(const std::string_view id, const std::shared_ptr<Texture>& value) noexcept;

        unsigned int get_attribute(const std::string& name) noexcept;

        void bind_output(const std::string& name, unsigned int channel) noexcept;

    private:
        std::string vertex_code;
        std::string fragment_code;
        glm::uint   program_id   = 0u;
        glm::uint   texture_slot = 0u;
    };
}

#endif
