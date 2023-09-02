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

#pragma once
#include "config.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <variant>

#include <glm/glm.hpp>

namespace pkzo
{
    using namespace glm;

    using UniformValue = std::variant<bool, int, uint, float,
                                      ivec2, uvec2, vec2,
                                      ivec3, uvec3, vec3,
                                      ivec4, uvec4, vec4,
                                      mat2,  mat3,  mat4>;

    //! GLSL Shader
    class PKZO_EXPORT Shader
    {
    public:
        static std::shared_ptr<Shader> load_file(const std::filesystem::path& file);

        Shader(const std::filesystem::path& file);
        Shader(const std::string& code);

        ~Shader();

        void set_code(const std::string& value) noexcept;

        const std::string& get_code() const noexcept;

        void compile();
        void compile(std::ostream& log);
        bool is_compiled() const noexcept;

        void bind();

        void set_uniform(const std::string_view name, const UniformValue& value) noexcept;

        int get_attribute(const std::string_view name) noexcept;

        void bind_output(const std::string_view name, uint channel) noexcept;

    private:
        uint program_id = 0;
        std::string code;

        Shader(const Shader&) = delete;
        const Shader& operator = (const Shader&) = delete;
    };
}

