/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef _PKZO_SHADER_H_
#define _PKZO_SHADER_H_

#include <string>
#include <rgm/rgm.h>

#include "defines.h"

namespace pkzo
{
    

    class PKZO_EXPORT Shader
    {
    public:

        Shader();

        Shader(const Shader&) = delete;

        ~Shader();

        const Shader& operator = (const Shader&) = delete;

        void set_vertex_code(const std::string& value);

        const std::string& get_vertex_code() const;

        void set_fragment_code(const std::string& value);

        const std::string& get_fragment_code() const;

        void load(const std::string& vertex_file, const std::string& fragment_file);

        void compile();

        void release();

        void bind();

        void unbind();

        void set_uniform(const std::string& name, int value);
        void set_uniform(const std::string& name, float value);
        void set_uniform(const std::string& name, rgm::vec2 value);
        void set_uniform(const std::string& name, rgm::ivec2 value);
        void set_uniform(const std::string& name, rgm::vec3 value);
        void set_uniform(const std::string& name, rgm::ivec3 value);
        void set_uniform(const std::string& name, rgm::vec4 value);
        void set_uniform(const std::string& name, rgm::ivec4 value);
        void set_uniform(const std::string& name, rgm::mat2 value);
        void set_uniform(const std::string& name, rgm::mat3 value);
        void set_uniform(const std::string& name, rgm::mat4 value);
        
    private:
        std::string vertex_code;
        std::string fragment_code;
        unsigned int program_id;
    };    
}

#endif
