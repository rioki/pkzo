// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Material.h"

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, const AlphaMode& mode)
    {
        switch (mode)
        {
        case AlphaMode::OPAQUE:
            os << "OPAQUE";
            break;
        case AlphaMode::MASK:
            os << "MASK";
            break;
        case AlphaMode::BLEND:
            os << "BLEND";
            break;
        }

        return os;
    }

    void to_json(nlohmann::json& j, const AlphaMode& mode)
    {
        switch (mode)
        {
        case AlphaMode::OPAQUE:
            j = "OPAQUE";
            break;
        case AlphaMode::MASK:
            j = "MASK";
            break;
        case AlphaMode::BLEND:
            j = "BLEND";
            break;
        }
    }

    void from_json(const nlohmann::json& j, AlphaMode& mode)
    {
        auto str = j.get<std::string>();
        if (str == "OPAQUE")
        {
            mode = AlphaMode::OPAQUE;
        }
        else if (str == "MASK")
        {
            mode = AlphaMode::MASK;
        }
        else if (str == "BLEND")
        {
            mode = AlphaMode::BLEND;
        }
        else
        {
            throw std::runtime_error("Invalid alpha mode.");
        }
    }

    Material::Material(const std::filesystem::path& f)
    : file(f)
    {
        auto dir = file.parent_path();

        auto in   = std::ifstream(file);
        auto json = nlohmann::json::parse(in);

        alpha_mode        = json.value("alphaMode", AlphaMode::OPAQUE);
        base_color_factor = json.value("baseColorFactor", glm::vec4(1.0f));
        metallic_factor   = json.value("metallicFactor", 1.0f);
        roughness_factor  = json.value("roughnessFactor", 1.0f);
        emissive_factor   = json.value("emissiveFactor", glm::vec3(0.0f));

        auto base_color_map_file = json.value("baseColorMap", std::string());
        if (!base_color_map_file.empty())
        {
            auto canonic_path = std::filesystem::weakly_canonical(dir / base_color_map_file);
            base_color_map = std::make_shared<Image>(canonic_path);
        }

        auto metallic_roughness_map_file = json.value("metallicRoughnessMap", std::string());
        if (!metallic_roughness_map_file.empty())
        {
            auto canonic_path = std::filesystem::weakly_canonical(dir / metallic_roughness_map_file);
            metallic_roughness_map = std::make_shared<Image>(canonic_path);
        }

        auto emissive_map_file = json.value("emissiveMap", std::string());
        if (!emissive_map_file.empty())
        {
            auto canonic_path = std::filesystem::weakly_canonical(dir / emissive_map_file);
            emissive_map = std::make_shared<Image>(canonic_path);
        }

        auto normal_map_file = json.value("normalMap", std::string());
        if (!normal_map_file.empty())
        {
            auto canonic_path = std::filesystem::weakly_canonical(dir / normal_map_file);
            normal_map = std::make_shared<Image>(canonic_path);
        }
    }

    bool Material::operator == (const Material& other) const noexcept
    {
        return alpha_mode == other.alpha_mode &&
               base_color_factor == other.base_color_factor &&
               base_color_map == other.base_color_map &&
               metallic_factor == other.metallic_factor &&
               roughness_factor == other.roughness_factor &&
               metallic_roughness_map == other.metallic_roughness_map &&
               emissive_factor == other.emissive_factor &&
               emissive_map == other.emissive_map &&
               normal_map == other.normal_map;
    }

    std::filesystem::path Material::get_file() const noexcept
    {
        return file;
    }

    void Material::set_alpha_mode(AlphaMode mode) noexcept
    {
        alpha_mode = mode;
    }

    AlphaMode Material::get_alpha_mode() const noexcept
    {
        return alpha_mode;
    }

    void Material::set_base_color_factor(const glm::vec4& factor) noexcept
    {
        base_color_factor = factor;
    }

    const glm::vec4& Material::get_base_color_factor() const noexcept
    {
        return base_color_factor;
    }

    void Material::set_base_color_map(const std::shared_ptr<Image>& texture) noexcept
    {
        base_color_map = texture;
    }

    const std::shared_ptr<Image>& Material::get_base_color_map() const noexcept
    {
        return base_color_map;
    }

    void Material::set_metallic_factor(float factor) noexcept
    {
        metallic_factor = factor;
    }

    float Material::get_metallic_factor() const noexcept
    {
        return metallic_factor;
    }

    void Material::set_roughness_factor(float factor) noexcept
    {
        roughness_factor = factor;
    }

    float Material::get_roughness_factor() const noexcept
    {
        return roughness_factor;
    }

    void Material::set_metallic_roughness_map(const std::shared_ptr<Image>& texture) noexcept
    {
        metallic_roughness_map = texture;
    }

    const std::shared_ptr<Image>& Material::get_metallic_roughness_map() const noexcept
    {
        return metallic_roughness_map;
    }

    void Material::set_emissive_factor(const glm::vec3& factor) noexcept
    {
        emissive_factor = factor;
    }

    const glm::vec3&Material:: get_emissive_factor() const noexcept
    {
        return emissive_factor;
    }

    void Material::set_emissive_map(const std::shared_ptr<Image>& texture) noexcept
    {
        emissive_map = texture;
    }

    const std::shared_ptr<Image>& Material::get_emissive_map() const noexcept
    {
        return emissive_map;
    }

    void Material::set_normal_map(const std::shared_ptr<Image>& texture) noexcept
    {
        normal_map = texture;
    }

    const std::shared_ptr<Image>& Material::get_normal_map() const noexcept
    {
        return normal_map;
    }

    void Material::save(const std::filesystem::path& file) const
    {
        auto dir = file.parent_path();

        auto json = nlohmann::json();

        json["alphaMode"]       = alpha_mode;
        json["baseColorFactor"] = base_color_factor;
        json["metallicFactor"]  = metallic_factor;
        json["roughnessFactor"] = roughness_factor;
        json["emissiveFactor"]  = emissive_factor;

        if (base_color_map)
        {
            auto diff = std::filesystem::relative(base_color_map->get_file(), dir);
            json["baseColorMap"]= diff;
        }

        if (metallic_roughness_map)
        {
            auto diff = std::filesystem::relative(metallic_roughness_map->get_file(), dir);
            json["metallicRoughnessMap"] = diff;
        }

        if (emissive_map)
        {
            auto diff = std::filesystem::relative(emissive_map->get_file(), dir);
            json["emissiveMap"] = diff;
        }

        if (normal_map)
        {
            auto diff = std::filesystem::relative(normal_map->get_file(), dir);
            json["normalMap"] = diff;
        }

        std::ofstream out(file);
        out << json.dump(4);
    }
}
