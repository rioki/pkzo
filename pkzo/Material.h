//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include "config.h"

#include <filesystem>
#include <memory>
#include <glm/glm.hpp>

namespace pkzo
{
    class Parameters;
    class Texture;
    class Material;

    PKZO_EXPORT std::shared_ptr<Texture> single_color_texture(std::byte value);
    PKZO_EXPORT std::shared_ptr<Texture> single_color_texture(float value);
    PKZO_EXPORT std::shared_ptr<Texture> single_color_texture(std::byte r, std::byte g, std::byte b);
    PKZO_EXPORT std::shared_ptr<Texture> single_color_texture(float r, float g, float b);
    PKZO_EXPORT std::shared_ptr<Texture> make_color_texture(const glm::vec3& color) noexcept;
    PKZO_EXPORT std::shared_ptr<Texture> make_black_texture() noexcept;

    PKZO_EXPORT std::shared_ptr<Texture> default_diffuse_texture();
    PKZO_EXPORT std::shared_ptr<Texture> default_specular_texture();
    PKZO_EXPORT std::shared_ptr<Texture> default_roughtness_texture();
    PKZO_EXPORT std::shared_ptr<Texture> default_normal_texture();
    PKZO_EXPORT std::shared_ptr<Texture> default_emissive_texture();
    PKZO_EXPORT std::shared_ptr<Texture> default_mask_texture();

    //! Make a plain emisisve material.
    //!
    //! @param color the color and intensity of the emissive material.
    PKZO_EXPORT std::shared_ptr<Material> make_emissive_material(const glm::vec3& color) noexcept;
    //! Make an emisisve material from a texture..
    //!
    //! @param texture the textreu emissive material.
    PKZO_EXPORT std::shared_ptr<Material> make_emissive_material(const std::shared_ptr<Texture>& texture) noexcept;

    //! Material
    class PKZO_EXPORT Material
    {
    public:
        Material() noexcept = default;
        Material(const std::shared_ptr<Texture>& diffuse, const std::shared_ptr<Texture>& specular, const std::shared_ptr<Texture>& roughtness);
        Material(const std::shared_ptr<Texture>& diffuse, const std::shared_ptr<Texture>& specular, const std::shared_ptr<Texture>& roughtness, const std::shared_ptr<Texture>& normal);
        Material(const std::shared_ptr<Texture>& diffuse, const std::shared_ptr<Texture>& specular, const std::shared_ptr<Texture>& roughtness, const std::shared_ptr<Texture>& normal, const std::shared_ptr<Texture>& emissive);
        Material(const std::shared_ptr<Texture>& diffuse, const std::shared_ptr<Texture>& specular, const std::shared_ptr<Texture>& roughtness, const std::shared_ptr<Texture>& normal, const std::shared_ptr<Texture>& emissive, const std::shared_ptr<Texture>& mask);
        Material(const std::filesystem::path& filename);

        void set_diffuse(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_diffuse() const noexcept;

        void set_specular(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_specular() const noexcept;

        void set_roughtness(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_roughtness() const noexcept;

        void set_normal(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_normal() const noexcept;

        void set_emissive(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_emissive() const noexcept;

        void set_mask(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_mask() const noexcept;

        std::shared_ptr<Parameters> to_parameters() const noexcept;

    private:
        std::shared_ptr<Texture> diffuse    = default_diffuse_texture();
        std::shared_ptr<Texture> specular   = default_specular_texture();
        std::shared_ptr<Texture> roughtness = default_roughtness_texture();
        std::shared_ptr<Texture> normal     = default_normal_texture();
        std::shared_ptr<Texture> emissive   = default_emissive_texture();
        std::shared_ptr<Texture> mask       = default_mask_texture();
    };
}