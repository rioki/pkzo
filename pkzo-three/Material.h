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
#include <pkzo/config.h>

#include <glm/glm.hpp>

#include <pkzo/Texture.h>

namespace pkzo::three
{
    //! Get a 1x1 white texture.
    //!
    //! This function returns a 1x1 white texture. The texture is cached for performance.
    //! @return Shared pointer to the 1x1 white texture.
    PKZO_EXPORT std::shared_ptr<Texture> get_white_texture();

    //! Get a 1x1 black texture.
    //!
    //! This function returns a 1x1 black texture. The texture is cached for performance.
    //! @return Shared pointer to the 1x1 black texture.
    PKZO_EXPORT std::shared_ptr<Texture> get_black_texture();

    //! Get a 1x1 normal map texture.
    //!
    //! This function returns a 1x1 normal map texture. The texture is cached for performance.
    //! @return Shared pointer to the 1x1 normal map texture.
    PKZO_EXPORT std::shared_ptr<Texture> get_normal_texture();

    //! Get a 1x1 orange texture.
    //!
    //! This function returns a 1x1 orange texture. The texture is cached for performance.
    //! @return Shared pointer to the 1x1 orange texture.
    PKZO_EXPORT std::shared_ptr<Texture> get_orange_texture();

    //! @brief Convert RGB color from hexadecimal to glm::vec3.
    //!
    //! @param hex The RGB color in hexadecimal format (e.g., 0xFF0000 for red).
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(unsigned int hex);

    //! @brief Convert RGBA color from hexadecimal to glm::vec4.
    //!
    //! @param hex The RGBA color in hexadecimal format (e.g., 0xFF0000FF for red, fully opaque).
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(unsigned int hex);

    //! Convert RGB color from separate 0-255 components to glm::vec3.
    //!
    //! @param r Red component, in [0, 255].
    //! @param g Green component, in [0, 255].
    //! @param b Blue component, in [0, 255].
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b);

    //! Convert RGBA color from separate 0-255 components to glm::vec4.
    //!
    //! @param r Red component, in [0, 255].
    //! @param g Green component, in [0, 255].
    //! @param b Blue component, in [0, 255].
    //! @param a Alpha component, in [0, 255].
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

    //! Convert RGB color from separate float components to glm::vec3.
    //!
    //! @param r Red component, in [0.0, 1.0].
    //! @param g Green component, in [0.0, 1.0].
    //! @param b Blue component, in [0.0, 1.0].
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(float r, float g, float b);

    //! Convert RGBA color from separate float components to glm::vec4.
    //!
    //! @param r Red component, in [0.0, 1.0].
    //! @param g Green component, in [0.0, 1.0].
    //! @param b Blue component, in [0.0, 1.0].
    //! @param a Alpha component, in [0.0, 1.0].
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(float r, float g, float b, float a);

    //! PBR Material class.
    class PKZO_EXPORT Material
    {
    public:
        Material() = default;
        Material(const Material&) = default;
        Material(Material&&) = default;

        Material(const glm::vec3& base_color_factor,
                 const std::shared_ptr<Texture>& base_color_map,
                 const std::shared_ptr<Texture>& metallic_roughness_map,
                 const std::shared_ptr<Texture>& normal_map,
                 const std::shared_ptr<Texture>& occlusion_map,
                 const glm::vec3& emissive_factor,
                 const std::shared_ptr<Texture>& emissive_map);

        ~Material() = default;

        Material& operator=(const Material&) = default;
        Material& operator=(Material&&) = default;

        //! Gets the base color factor.
        //!
        //! @return The base color factor.
        glm::vec3 get_base_color_factor() const;

        //! Sets the base color factor.
        //! @param color The new base color factor.
        void set_base_color_factor(const glm::vec3& color);

        //! Gets the emissive factor.
        //!
        //! @return The emissive factor.
        glm::vec3 get_emissive_factor() const;

        //! Sets the emissive factor.
        //!
        //! @param factor The new emissive factor.
        void set_emissive_factor(const glm::vec3& factor);

        //! Gets the base color texture.
        //!
        //! @return The base color texture.
        std::shared_ptr<Texture> get_base_color_map() const;

        //! Sets the base color texture.
        //! @param texture The new base color texture.
        void set_base_color_map(const std::shared_ptr<Texture>& value);

        //! Gets the metallic roughness texture.
        //!
        //! @return The metallic roughness texture.
        std::shared_ptr<Texture> get_metallic_roughness_map() const;

        //! Sets the metallic roughness texture.
        //!
        //! @param texture The new metallic roughness texture.
        void set_metallic_roughness_map(const std::shared_ptr<Texture>& value);

        //! Gets the normal texture.
        //!
        //! @return The normal texture.
        std::shared_ptr<Texture> get_normal_map() const;

        //! Sets the normal texture.
        //! @param texture The new normal texture.
        void set_normal_map(const std::shared_ptr<Texture>& value);

        //! Gets the occlusion texture.
        //!
        //! @return The occlusion texture.
        std::shared_ptr<Texture> get_occlusion_map() const;

        //! Sets the occlusion texture.
        //!
        //! @param texture The new occlusion texture.
        void set_occlusion_map(const std::shared_ptr<Texture>& value);

        //! Gets the emissive texture.
        //!
        //! @return The emissive texture.
        std::shared_ptr<Texture> get_emissive_map() const;

        //! Sets the emissive texture.
        //!
        //! @param texture The new emissive texture.
        void set_emissive_map(const std::shared_ptr<Texture>& value);

    private:
        glm::vec3                base_color_factor      = {1.0f, 1.0f, 1.0f};
        glm::vec3                emissive_factor        = {0.0f, 0.0f, 0.0f};
        std::shared_ptr<Texture> base_color_map         = get_white_texture();
        std::shared_ptr<Texture> metallic_roughness_map = get_black_texture();
        std::shared_ptr<Texture> normal_map             = get_normal_texture();
        std::shared_ptr<Texture> occlusion_map          = get_black_texture();
        std::shared_ptr<Texture> emissive_map           = get_black_texture();
    };

    //! Creates an opaque material with a base color.
    //!
    //! @param base_color A glm::vec3 representing the base RGB color.
    //! @return A std::shared_ptr<Material> of the created Material object.
    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const glm::vec3& base_color);

    //! Creates an opaque material with textures for base color and metallic-roughness.
    //!
    //! @param base_color Shared pointer to the base color texture.
    //! @param metallic_roughness Shared pointer to the metallic-roughness texture.
    //! @return A std::shared_ptr<Material> of the created Material object.
    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const std::shared_ptr<Texture>& base_color, const std::shared_ptr<Texture>& metallic_roughness);

    //! Creates an opaque material with additional normal texture.
    //!
    //! @param base_color Shared pointer to the base color texture.
    //! @param metallic_roughness Shared pointer to the metallic-roughness texture.
    //! @param normal Shared pointer to the normal texture.
    //! @return A std::shared_ptr<Material> of the created Material object.
    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const std::shared_ptr<Texture>& base_color, const std::shared_ptr<Texture>& metallic_roughness, const std::shared_ptr<Texture>& normal);

    //! Creates an emissive material with an RGB factor.
    //!
    //! @param factor A glm::vec3 representing the emission factor.
    //! @return A std::shared_ptr<Material> of the created Material object.
    PKZO_EXPORT std::shared_ptr<Material> create_emissive_material(const glm::vec3& factor);

    //! Creates an emissive material with a texture map.
    //!
    //! @param map Shared pointer to the emissive texture map.
    //! @return A std::shared_ptr<Material> of the created Material object.
    PKZO_EXPORT std::shared_ptr<Material> create_emissive_material(const std::shared_ptr<Texture>& map);
}
