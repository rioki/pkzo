// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MATERIAL_H_
#define _PKZO_MATERIAL_H_

#include <memory>
#include <filesystem>
#include <string>
#include <map>
#include <glm/glm.hpp>

#include "defines.h"
#include "UniformValue.h"

namespace fs = std::filesystem;

namespace pkzo
{
    class Texture;
    class Shader;

    /*!
     * Graphica material.
     */
    class PKZO_EXPORT Material
    {
    public:

        /*!
         * Construct defunct material.
         *
         * Default constucted materials are nor usable, set a shaders
         * and the aproproate uniforms and textures to use it.
         */
        Material();

        /*!
         * Load material from file.
         *
         * @param file the file to load from
         */
        explicit Material(const fs::path& file);

        ~Material();

        /*!
         * Check if a uniform variable exists.
         *
         * @param id the id of the unifrom variable
         * @return true if the uniform with the given id exists.
         */
        bool has_uniform(const std::string& id) const;

        /*!
         * Get a uniform variable.
         *
         * @param id the id of the unifrom variable
         * @return the value of the uniform variable with the given id
         *
         * @throws std::runtime_error if the uniform is not defined in the material
         */
        const UniformValue& get_uniform(const std::string& id) const;

        /*!
         * Set a uniform variable.
         *
         * @param id the id of the uniform variable
         * @param value the value for the uniform variable
         */
        void set_uniform(const std::string& id, const UniformValue& value);

        /*!
         * Check if a texture exists.
         *
         * @param id the id of the texture
         * @return true if the texture with the given id exists.
         */
        bool has_texture(const std::string& id) const;

        /*!
         * Get a texture.
         *
         * @param id the id of the texture
         * @return the texture with the given id
         *
         * @throws std::runtime_error if the texture is not defined in the material
         */
        const std::shared_ptr<Texture>& get_texture(const std::string& id) const;

        /*!
         * Set a texture.
         *
         * @param id the id of the texture
         * @param value the texture
         */
        void set_texture(const std::string& id, const std::shared_ptr<Texture>& value);

        /*!
         * Get the shader.
         *
         * @return the shader
         */
        const std::shared_ptr<Shader>& get_shader() const;

        /*!
         * Set the shader.
         *
         * @param the shader
         */
        void set_shader(const std::shared_ptr<Shader>& value);

        void bind(Shader& shader);
        void unbind();

        /*!
         * Swap internals with other material
         *
         * @param other the other material
         */
        void swap(Material& other) noexcept;

    private:
        std::map<std::string, UniformValue> uniforms;
        std::map<std::string, std::shared_ptr<Texture>> textures;
        std::shared_ptr<Shader> shader;

        void load(const fs::path& file);

    };
}

#endif
