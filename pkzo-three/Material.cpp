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

#include "Material.h"

namespace pkzo::three
{
    std::shared_ptr<Texture> get_white_texture()
    {
        static auto white_texture = Texture::create_from_buffer(glm::uvec2(1, 1), ColorMode::RGBA, DataType::UINT8, "\xFF\xFF\xFF\xFF");
        return white_texture;
    }

    std::shared_ptr<Texture> get_black_texture()
    {
        static auto black_texture = Texture::create_from_buffer(glm::uvec2(1, 1), ColorMode::RGBA, DataType::UINT8, "\x00\x00\x00\xFF");
        return black_texture;
    }

    std::shared_ptr<Texture> get_normal_texture()
    {
        // Assuming normal is in (x,y,z) = (0, 0, 1) mapped to (r,g,b) = (128, 128, 255)
        static auto normal_texture = Texture::create_from_buffer(glm::uvec2(1, 1), ColorMode::RGBA, DataType::UINT8, "\x80\x80\xFF\xFF");
        return normal_texture;
    }

    std::shared_ptr<Texture> get_orange_texture()
    {
        // RGBA for orange is (255, 165, 0, 255)
        static auto orange_texture = Texture::create_from_buffer(glm::uvec2(1, 1), ColorMode::RGBA, DataType::UINT8, "\xFF\xA5\x00\xFF");
        return orange_texture;
    }

    glm::vec3 rgb(unsigned int hex)
    {
        auto r = (hex >> 16) & 0xFF;
        auto g = (hex >> 8) & 0xFF;
        auto b = hex & 0xFF;
        return rgb(r, g, b);
    }

    glm::vec4 rgba(unsigned int hex)
    {
        auto r = (hex >> 24) & 0xFF;
        auto g = (hex >> 16) & 0xFF;
        auto b = (hex >> 8) & 0xFF;
        auto a = hex & 0xFF;
        return rgba(r, g, b, a);
    }

    glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b)
    {
        return rgb(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    {
        return rgba(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    glm::vec3 rgb(float r, float g, float b)
    {
        return glm::vec3(r, g, b);
    }

    glm::vec4 rgba(float r, float g, float b, float a)
    {
        return glm::vec4(r, g, b, a);
    }

    glm::vec3 Material::get_base_color_factor() const
    {
        return base_color_factor;
    }

    Material::Material(const glm::vec3& base_color_factor,
                       const std::shared_ptr<Texture>& base_color_map,
                       const std::shared_ptr<Texture>& metallic_roughness_map,
                       const std::shared_ptr<Texture>& normal_map,
                       const std::shared_ptr<Texture>& occlusion_map,
                       const glm::vec3& emissive_factor,
                       const std::shared_ptr<Texture>& emissive_map)
    : base_color_factor(base_color_factor),
      emissive_factor(emissive_factor),
      base_color_map(base_color_map),
      metallic_roughness_map(metallic_roughness_map),
      normal_map(normal_map),
      occlusion_map(occlusion_map),
      emissive_map(emissive_map)

    {}

    void Material::set_base_color_factor(const glm::vec3& color)
    {
        check(glm::all(glm::greaterThanEqual(color, glm::vec3(0.0f))));
        check(glm::all(glm::lessThanEqual(color, glm::vec3(1.0f))));
        base_color_factor = color;
    }

    glm::vec3 Material::get_emissive_factor() const
    {
        return emissive_factor;
    }

    void Material::set_emissive_factor(const glm::vec3& factor)
    {
        check(glm::all(glm::greaterThanEqual(factor, glm::vec3(0.0f))));
        emissive_factor = factor;
    }

    std::shared_ptr<Texture> Material::get_base_color_map() const
    {
        return base_color_map;
    }

    void Material::set_base_color_map(const std::shared_ptr<Texture>& value)
    {
        check(value != nullptr);
        base_color_map = value;
    }

    std::shared_ptr<Texture> Material::get_metallic_roughness_map() const
    {
        return metallic_roughness_map;
    }

    void Material::set_metallic_roughness_map(const std::shared_ptr<Texture>& value)
    {
        check(value != nullptr);
        metallic_roughness_map = value;
    }

    std::shared_ptr<Texture> Material::get_normal_map() const
    {
        return normal_map;
    }

    void Material::set_normal_map(const std::shared_ptr<Texture>& value)
    {
        check(value != nullptr);
        normal_map = value;
    }

    std::shared_ptr<Texture> Material::get_occlusion_map() const
    {
        return occlusion_map;
    }

    void Material::set_occlusion_map(const std::shared_ptr<Texture>& value)
    {
        check(value != nullptr);
        occlusion_map = value;
    }

    std::shared_ptr<Texture> Material::get_emissive_map() const
    {
        return emissive_map;
    }

    void Material::set_emissive_map(const std::shared_ptr<Texture>& value)
    {
        check(value != nullptr);
        emissive_map = value;
    }

    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const glm::vec3& base_color)
    {
        return std::make_shared<Material>(base_color, get_white_texture(), get_black_texture(), get_normal_texture(), get_black_texture(), glm::vec3(0.0f), get_black_texture());
    }

    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const std::shared_ptr<Texture>& base_color, const std::shared_ptr<Texture>& metallic_roughness)
    {
        return std::make_shared<Material>(glm::vec3(1.0f), base_color, metallic_roughness, get_normal_texture(), get_black_texture(), glm::vec3(0.0f), get_black_texture());
    }

    PKZO_EXPORT std::shared_ptr<Material> create_opaque_material(const std::shared_ptr<Texture>& base_color, const std::shared_ptr<Texture>& metallic_roughness, const std::shared_ptr<Texture>& normal)
    {
        return std::make_shared<Material>(glm::vec3(1.0f), base_color, metallic_roughness, normal, get_black_texture(), glm::vec3(0.0f), get_black_texture());
    }

    PKZO_EXPORT std::shared_ptr<Material> create_emissive_material(const glm::vec3& factor)
    {
        return std::make_shared<Material>(glm::vec3(1.0f), get_white_texture(), get_black_texture(), get_normal_texture(), get_black_texture(), factor, get_black_texture());
    }

    PKZO_EXPORT std::shared_ptr<Material> create_emissive_material(const std::shared_ptr<Texture>& map)
    {
        return std::make_shared<Material>(glm::vec3(1.0f), get_white_texture(), get_black_texture(), get_normal_texture(), get_black_texture(), glm::vec3(1.0f), map);
    }
}
