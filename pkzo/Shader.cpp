//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#include "Shader.h"

#include "fs.h"

#include <GL/glew.h>

namespace pkzo
{
    Shader::Shader()
    : program_id(0) {}

    Shader::~Shader()
    {
        release();
    }

    void Shader::set_vertex_code(const std::string& value)
    {
        vertex_code = value;    
    }

    const std::string& Shader::get_vertex_code() const
    {
        return vertex_code;    
    }

    void Shader::set_fragment_code(const std::string& value)
    {
        fragment_code = value;
    }

    const std::string& Shader::get_fragment_code() const
    {
        return fragment_code;    
    }

    void Shader::load(const std::string& vertex_file, const std::string& fragment_file)
    {
        vertex_code   = fs::read(vertex_file);   
        fragment_code = fs::read(fragment_file);
    }

    void Shader::compile()
    {
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

        program_id = glCreateProgram();
        glAttachShader(program_id, vertex_id);
        glAttachShader(program_id, fragment_id);
        glLinkProgram(program_id);

        glGetShaderInfoLog(program_id, 256, NULL, logstr);

        glGetShaderiv(program_id, GL_LINK_STATUS, &status);
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
    }

    void Shader::release()
    {
        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
        }
    }

    void Shader::bind()
    {
        if (program_id == 0)
        {
            compile();
        }

        glUseProgram(program_id);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }  
    
    int Shader::get_uniform_location(const std::string& name) const
    {
        return glGetUniformLocation(program_id, name.c_str());
    }

    void Shader::set_uniform(const std::string& name, int value)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform1i(location, value);            
        }
    }

    void Shader::set_uniform(const std::string& name, float value)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform1f(location, value);
        }        
    }

    void Shader::set_uniform(const std::string& name, int x, int y)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform2i(location, x, y);
        }
    }
    
    void Shader::set_uniform(const std::string& name, float x, float y)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform2f(location, x, y);
        }
    }

    void Shader::set_uniform(const std::string& name, int x, int y, int z)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform3i(location, x, y, z);
        }
    }

    void Shader::set_uniform(const std::string& name, float x, float y, float z)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform3f(location, x, y, z);
        }
    }

    void Shader::set_uniform(const std::string& name, int x, int y, int z, int m)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform4i(location, x, y, z, m);
        }
    }
    
    void Shader::set_uniform(const std::string& name, float x, float y, float z, float m)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            glUniform4f(location, x, y, z, m);
        }
    }

    void Shader::set_uniform(const std::string& name, int* values, int size)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            switch (size)
            {
            case 1:
                glUniform1iv(location, 1, values);
                break;
            case 2:
                glUniform2iv(location, 1, values);
                break;
            case 3:
                glUniform3iv(location, 1, values);
                break;
            case 4:
                glUniform4iv(location, 1, values);
                break;
            default:
                throw std::logic_error("Invalid matrix size.");
            }
        }
    }

    void Shader::set_uniform(const std::string& name, float* values, int size)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        if (location != -1)
        {
            switch (size)
            {
            case 1:
                glUniform1fv(location, 1, values);
                break;
            case 2:
                glUniform2fv(location, 1, values);
                break;
            case 3:
                glUniform3fv(location, 1, values);
                break;
            case 4:
                glUniform4fv(location, 1, values);
                break;
            default:
                throw std::logic_error("Invalid matrix size.");
            }
        }
    }
    
    void Shader::set_uniform_matrix(const std::string& name, float* values, int size, bool transpose)
    {
        int location = glGetUniformLocation(program_id, name.c_str());
        int glt      = transpose ? GL_TRUE : GL_FALSE;
        if (location != -1)
        {
            switch (size)
            {
                case 4:
                    glUniformMatrix2fv(location, 1, glt, values);
                    break;
                case 9:
                    glUniformMatrix3fv(location, 1, glt, values);
                    break;
                case 16:
                    glUniformMatrix4fv(location, 1, glt, values);
                    break;
                default:
                    throw std::logic_error("Invalid matrix size.");
            }       

        }        
    }

    int Shader::get_attribute_location(const std::string& name) const
    {
        return glGetAttribLocation(program_id, name.c_str());
    }
}
