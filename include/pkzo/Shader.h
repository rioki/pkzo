
#ifndef _PKZO_SHADER_H_
#define _PKZO_SHADER_H_

#include <string>

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

        int get_uniform_location(const std::string& name) const;

        void set_uniform(const std::string& name, int* values, int size);
        void set_uniform(const std::string& name, float* values, int size);

        void set_uniform_matrix(const std::string& name, float* values, int size, bool transpose = false);
                
        int get_attribute_location(const std::string& name) const;

    private:
        std::string vertex_code;
        std::string fragment_code;
        unsigned int program_id;
    };    
}

#endif
