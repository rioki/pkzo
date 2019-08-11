// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SHADER_H_
#define _PKZO_SHADER_H_

#include <memory>
#include <string>
#include <string_view>
#include <filesystem>
#include <glm/glm.hpp>

#include "defines.h"
#include "UniformValue.h"

namespace fs = std::filesystem;

namespace pkzo
{
    class Texture;

    /*!
     * GLSL Shader
     */
    class PKZO_EXPORT Shader
    {
    public:
        //! Create a dummy shader.
        Shader();

        //! Load shader from resoruce
        explicit Shader(uint16_t id);

        /*!
         * Load the shder from a file.
         *
         * @param file the file to laod
         */
        explicit Shader(const fs::path& file);
        Shader(const Shader&) = delete;
        ~Shader();
        const Shader& operator = (const Shader&) = delete;

        /*!
         * Set the GLSL code.
         *
         * @param value the code to set
         */
        void set_code(const std::string& value);

        /*!
         * Get the GLSL code.
         *
         * @retturn the code
         */
        const std::string& get_code();

        /*!
         * Bind the shader on the openGL context.
         */
        void bind();

        /*!
         * Unbind the shader.
         */
        void unbind();

        /*!
         * Set a uniform variable.
         *
         * @param id the id of the uniform variable
         * @param value the value for the uniform variable
         */
        void set_uniform(const std::string_view id, const UniformValue& value);

        /*!
         * Set a texture.
         *
         * @param id the id of the texture
         * @param value the texture
         *
         * @warning A call to bind will reset the texture slots.
         */
        void set_texture(const std::string_view id, const std::shared_ptr<Texture>& value);

        unsigned int get_attribute(const std::string_view name);
        void bind_output(const std::string_view name, unsigned int channel);

    private:
        std::string code;
        glm::uint   program_id = 0u;
        bool        bound = false;
        glm::uint   texture_slot = 0u;

        void compile();
    };
}

#endif
