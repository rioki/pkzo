
#ifndef _PKZO_SHADER_H_
#define _PKZO_SHADER_H_

#include <string>

#include "defines.h"

namespace pkzo
{
    /**
     * GLSL Shader Program
     **/
    class PKZO_EXPORT Shader
    {
    public:
        
        /**
         * Create a GLSL Shader Program
         **/
        Shader();

        Shader(const Shader&) = delete;

        /**
         * Destroy a GLSL Shader Program
         **/
        ~Shader();

        const Shader& operator = (const Shader&) = delete;

        /**
         * Set the Vertex Shader Code
         *
         * @param value the GLSL code of the vertex shader
         **/
        void set_vertex_code(const std::string& value);

        /**
         * Get the Vertex Shader Code
         *
         * @return the GLSL code of the vertex shader
         **/
        const std::string& get_vertex_code() const;

        /**
         * Set the Fragment Shader Code
         *
         * @param value the GLSL code of the fragment shader
         **/
        void set_fragment_code(const std::string& value);

        /**
         * Get the Fragment Shader Code
         *
         * @return the GLSL code of the fragment shader
         **/
        const std::string& get_fragment_code() const;

        /**
         * Load Vertex and Fragment Shaders from File
         *
         * @param vertex_file   the file containing the vertex shader
         * @param fragment_file the file containing the fragment shader
         **/
        void load(const std::string& vertex_file, const std::string& fragment_file);

        /**
         * Compile and Link the GLSL Program
         *
         * This function will compile and link the GLSL program. 
         *
         * @throws std::runtime_error If a compilation or link error is encountered,
         * a std::runtime_error is thrown.
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void compile();

        /**
         * Releases the Program from Video Memory
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void release();

        /**
         * Activate the GLSL Program
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void bind();

        /**
         * Deactivate the GLSL Program
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void unbind();

        /**
         * Get the Location of a Uniform Variable
         *
         * @name the name of the uniform
         *
         * @returns the location of the uniform variable
         *
         * @note The shader must be bound to call this function.
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        int get_uniform_location(const std::string& name) const;

        /**
         * Set the Value of a Uniform Variable
         *
         * @param name  the name of the variable
         * @param value the value of the variable
         *
         * @note The shader must be bound to call this function.
         * @warning This function can only be called with a valid and active OpenGL context.
         * @{
         **/
        void set_uniform(const std::string& name, int value);
        void set_uniform(const std::string& name, float value);
        /** @} **/


        /**
         * Set the Value of a Uniform Variable
         * 
         * @param name   the name of the variable
         * @param values an array of values
         * @param size   the number of values in the values array
         *
         * @note The shader must be bound to call this function.
         * @warning This function can only be called with a valid and active OpenGL context.
         *
         * @todo support 9 and 16 as glUniformMatrix3fv, glUniformMatrix4fv?
         * @{
         **/
        void set_uniform(const std::string& name, int* values, int size);
        void set_uniform(const std::string& name, float* values, int size);
        /** @} **/

        /**
         * Set the Value of a Uniform Matrix Variable
         * 
         * @param name      the name of the variable
         * @param values    an array of values
         * @param size      the number of values in the values array
         * @param transpose transpose the matrix
         *
         * @note The shader must be bound to call this function.
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void set_uniform_matrix(const std::string& name, float* values, int size, bool transpose = false);
              
        /**
         * Get the Location of a Attibute Variable
         *
         * @name the name of the attribute
         *
         * @returns the location of the attribute variable
         *
         * @note The shader must be bound to call this function.
         * @warning This function can only be called with a valid and active OpenGL context.
         **/        
        int get_attribute_location(const std::string& name) const;

    private:
        std::string vertex_code;
        std::string fragment_code;
        unsigned int program_id;
    };    
}

#endif
