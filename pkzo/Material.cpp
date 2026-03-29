// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Material.h"

#include <fstream>

#include <fkYAML/node.hpp>

#include <pkzo/color.h>

namespace pkzo
{
    glm::vec3 load_yaml_color3(const fkyaml::node& yaml, const std::string& id, const glm::vec3& fallback)
    {
        if (yaml.contains(id))
        {
            return yaml[id].get_value<pkzo::color3>();
        }
        return fallback;
    }

    float load_yaml_float(const fkyaml::node& yaml, const std::string& id, const float& fallback)
    {
        if (yaml.contains(id))
        {
            return static_cast<float>(yaml[id].get_value<float>());
        }
        return fallback;
    }

    std::shared_ptr<Texture> load_yaml_texture(std::filesystem::path& base, const fkyaml::node& yaml, const std::string& id, const std::shared_ptr<Texture>& fallback)
    {
        if (yaml.contains(id))
        {
            return Texture::load_file({
                .file = base / yaml[id].get_value<std::string>()
            });
        }
        return fallback;
    }

    auto load_material_yaml(const std::filesystem::path& file)
    {
        auto init = Material::Props{};

        auto input = std::ifstream(file);
        if (!input)
        {
            throw std::runtime_error(tfm::format("Failed to open %s for reading.", file));
        }

        auto base = file.parent_path();

        auto yaml = fkyaml::node::deserialize(input);
        init.opacity_factor         = load_yaml_float(yaml,         "opacity_factor",         init.opacity_factor);
        init.metallic_roughness_map = load_yaml_texture(base, yaml, "metallic_roughness_map", init.metallic_roughness_map);
        init.base_color_factor      = load_yaml_color3(yaml,        "base_color_factor",      init.base_color_factor);
        init.base_color_map         = load_yaml_texture(base, yaml, "base_color_map",         init.base_color_map);
        init.roughness_factor       = load_yaml_float(yaml,         "roughness_factor",       init.roughness_factor);
        init.metallic_factor        = load_yaml_float(yaml,         "metallic_factor",        init.metallic_factor);
        init.metallic_roughness_map = load_yaml_texture(base, yaml, "metallic_roughness_map", init.metallic_roughness_map);
        init.emissive_factor        = load_yaml_color3(yaml,        "emissive_factor",        init.emissive_factor);
        init.emissive_map           = load_yaml_texture(base, yaml, "emissive_map",           init.emissive_map);
        init.normal_map             = load_yaml_texture(base, yaml, "normal_map",             init.normal_map);

        return init;
    }

    Material::Material(const std::filesystem::path& file)
    : Material(load_material_yaml(file)) {}

    Material::Material(Props init)
    : opacity_factor(init.opacity_factor),
      base_color_factor(init.base_color_factor),
      base_color_map(init.base_color_map),
      roughness_factor(init.roughness_factor),
      metallic_factor(init.metallic_factor),
      metallic_roughness_map(init.metallic_roughness_map),
      normal_map(init.normal_map),
      emissive_factor(init.emissive_factor),
      emissive_map(init.emissive_map) {}

    Material::~Material() = default;

    float Material::get_opacity_factor() const
    {
        return opacity_factor;
    }

    const glm::vec3& Material::get_base_color_factor() const
    {
        return base_color_factor;
    }

    std::shared_ptr<Texture> Material::get_base_color_map() const
    {
        return base_color_map;
    }

    float Material::get_roughness_factor() const
    {
        return roughness_factor;
    }

    float Material::get_metallic_factor() const
    {
        return metallic_factor;
    }

    std::shared_ptr<Texture> Material::get_metallic_roughness_map() const
    {
        return metallic_roughness_map;
    }

    std::shared_ptr<Texture> Material::get_normal_map() const
    {
        return normal_map;
    }

    const glm::vec3& Material::get_emissive_factor() const
    {
        return emissive_factor;
    }

    std::shared_ptr<Texture> Material::get_emissive_map() const
    {
        return emissive_map;
    }
}