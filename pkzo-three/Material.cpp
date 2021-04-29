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

#include "pch.h"
#include "Material.h"

namespace pkzo::three
{
    void Material::set_base_color_factor(const glm::vec3& value) noexcept
    {
        base_color_factor = value;
    }

    const glm::vec3& Material::get_base_color_factor() const noexcept
    {
        return base_color_factor;
    }

    void Material::set_base_color_map(const std::shared_ptr<Texture>& value) noexcept
    {
        base_color_map = value;
    }

    const std::shared_ptr<Texture>& Material::get_base_color_map() const noexcept
    {
        return base_color_map;
    }

    void Material::set_roughness_factor(float value) noexcept
    {
        roughness_factor = value;
    }

    float Material::get_roughness_factor() const noexcept
    {
        return roughness_factor;
    }

    void Material::set_metallic_factor(float value) noexcept
    {
        metallic_factor = value;
    }

    float Material::get_metallic_factor() const noexcept
    {
        return metallic_factor;
    }

    void Material::set_metallic_roughtness_map(const std::shared_ptr<Texture>& value) noexcept
    {
        metallic_roughtness_map = value;
    }

    const std::shared_ptr<Texture>& Material::get_metallic_roughtness_map() const noexcept
    {
        return metallic_roughtness_map;
    }

    void Material::set_normal_map(const std::shared_ptr<Texture>& value) noexcept
    {
        normal_map = value;
    }

    const std::shared_ptr<Texture>& Material::get_normal_map() const noexcept
    {
        return normal_map;
    }

    void Material::set_emissive_factor(const glm::vec3& value) noexcept
    {
        emissive_factor = value;
    }

    const glm::vec3& Material::get_emissive_factor() const noexcept
    {
        return emissive_factor;
    }

    void Material::set_emissive_map(const std::shared_ptr<Texture>& value) noexcept
    {
        emissive_map = value;
    }

    const std::shared_ptr<Texture>& Material::get_emissive_map() const noexcept
    {
        return emissive_map;
    }

    std::shared_ptr<Parameters> Material::to_parameters() const noexcept
    {
        auto params = std::make_shared<Parameters>();

        params->set_value("pkzo_BaseColorFactor", base_color_factor);
        if (base_color_map)
        {
            params->set_value("pkzo_HasBaseColorMap", true);
            params->set_value("pkzo_BaseColorMap", base_color_map);
        }
        else
        {
            params->set_value("pkzo_HasBaseColorMap", false);
        }
        params->set_value("pkzo_RoughnessFactor", roughness_factor);
        params->set_value("pkzo_MetallicFactor", metallic_factor);
        if (metallic_roughtness_map)
        {
            params->set_value("pkzo_HasMetallicRoughtnessMap", true);
            params->set_value("pkzo_MetallicRoughtnessMap", metallic_roughtness_map);
        }
        else
        {
            params->set_value("pkzo_HasMetallicRoughtnessMap", false);
        }
        if (normal_map)
        {
            params->set_value("pkzo_HasNormalMap", true);
            params->set_value("pkzo_NormalMap", normal_map);
        }
        else
        {
            params->set_value("pkzo_HasNormalMap", false);
        }
        params->set_value("pkzo_EmissiveFactor", emissive_factor);
        if (emissive_map)
        {
            params->set_value("pkzo_HasEmissiveMap", true);
            params->set_value("pkzo_EmissiveMap", emissive_map);
        }
        else
        {
            params->set_value("pkzo_HasEmissiveMap", false);
        }

        return params;
    }
}