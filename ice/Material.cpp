// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "Material.h"

namespace ice
{
    void Material::set_base_color_factor(const glm::vec4& value) noexcept
    {
        base_color_factor = value;
        increment_version();
    }

    const glm::vec4& Material::get_base_color_factor() const noexcept
    {
        return base_color_factor;
    }

    void Material::set_base_color_map(const std::shared_ptr<ice::Texture>& value) noexcept
    {
        base_color_map = value;
        increment_version();
    }

    const std::shared_ptr<ice::Texture>& Material::get_base_color_map() const noexcept
    {
        return base_color_map;
    }

    void Material::set_emissive_factor(const glm::vec3& value) noexcept
    {
        emissive_factor = value;
        increment_version();
    }

    const glm::vec3& Material::get_emissive_factor() const noexcept
    {
        return emissive_factor;
    }

    void Material::set_emissive_map(const std::shared_ptr<ice::Texture>& value) noexcept
    {
        emissive_map = value;
        increment_version();
    }

    const std::shared_ptr<ice::Texture>& Material::get_emissive_map() const noexcept
    {
        return emissive_map;
    }

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec3& factor) noexcept
    {
        return make_simple_material(glm::vec4(factor, 1.0f), nullptr);
    }

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec3& factor, const std::shared_ptr<ice::Texture>& map) noexcept
    {
        return make_simple_material(glm::vec4(factor, 1.0f), map);
    }

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec4& factor) noexcept
    {
        return make_simple_material(factor, nullptr);
    }

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const std::shared_ptr<ice::Texture>& map) noexcept
    {
        return make_simple_material(glm::vec4(1.0f), map);
    }

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec4& factor, const std::shared_ptr<ice::Texture>& map) noexcept
    {
        auto material = std::make_shared<Material>();

        material->set_base_color_factor(factor);
        material->set_base_color_map(map);

        return material;
    }

    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const glm::vec3& factor) noexcept
    {
        return make_emissive_material(factor, nullptr);
    }

    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const std::shared_ptr<ice::Texture>& map) noexcept
    {
        return make_emissive_material(glm::vec3(1.0f), map);
    }

    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const glm::vec3& factor, const std::shared_ptr<ice::Texture>& map) noexcept
    {
        auto material = std::make_shared<Material>();

        material->set_base_color_factor(glm::vec4(0.0f));
        material->set_emissive_factor(factor);
        material->set_emissive_map(map);

        return material;
    }
}
