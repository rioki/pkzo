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

#include "glmio.h"
#include "compose.h"
#include "Texture.h"
#include "Parameters.h"

namespace pkzo
{
    std::shared_ptr<Texture> single_color_texture(std::byte value)
    {
        static std::map<std::byte, std::weak_ptr<Texture>> cache;
        std::shared_ptr<Texture> result;

        auto i = cache.find(value);
        if (i != end(cache))
        {
            result = i->second.lock();
        }

        if (!result)
        {
            result = std::make_shared<Texture>(glm::uvec2(1), ColorMode::R, DataType::UINT8, &value, compose("Single Color %0", value));
            cache[value] = result;
        }

        return result;
    }

    std::shared_ptr<Texture> single_color_texture(float value)
    {
        DBG_ASSERT(value <= 1.0f);
        DBG_ASSERT(value >= 0.0f);
        return single_color_texture(static_cast<std::byte>(value * 255.0f));
    }

    std::shared_ptr<Texture> single_color_texture(std::byte r, std::byte g, std::byte b)
    {
        static std::map<std::tuple<std::byte, std::byte, std::byte>, std::weak_ptr<Texture>> cache;
        std::shared_ptr<Texture> result;

        auto idx = std::make_tuple(r, g, b);
        auto i = cache.find(idx);
        if (i != end(cache))
        {
            result = i->second.lock();
        }

        if (!result)
        {
            std::byte mem[3] = {r, g, b};
            result = std::make_shared<Texture>(glm::uvec2(1), ColorMode::RGB, DataType::UINT8, &mem, compose("Single Color (%0, %1, %2)", r, g, b));
            cache[idx] = result;
        }

        return result;
    }

    std::shared_ptr<Texture> single_color_texture(float r, float g, float b)
    {
        DBG_ASSERT(r <= 1.0f);
        DBG_ASSERT(r >= 0.0f);
        DBG_ASSERT(g <= 1.0f);
        DBG_ASSERT(g >= 0.0f);
        DBG_ASSERT(b <= 1.0f);
        DBG_ASSERT(b >= 0.0f);
        return single_color_texture(static_cast<std::byte>(r * 255.0f), static_cast<std::byte>(g * 255.0f), static_cast<std::byte>(b * 255.0f));
    }

    std::shared_ptr<Texture> make_color_texture(const glm::vec3& color) noexcept
    {
        return single_color_texture(color.x, color.y, color.z);
    }

    std::shared_ptr<Texture> make_black_texture() noexcept
    {
        return single_color_texture(0, 0, 0);
    }

    std::shared_ptr<Texture> default_diffuse_texture()
    {
        return single_color_texture(0.75f, 0.75f, 0.75f);
    }

    std::shared_ptr<Texture> default_specular_texture()
    {
        return single_color_texture(0.04f, 0.04f, 0.04f);
    }

    std::shared_ptr<Texture> default_roughtness_texture()
    {
        return single_color_texture(0.5f);
    }

    std::shared_ptr<Texture> default_normal_texture()
    {
        return single_color_texture(0.5f, 0.5f, 1.0f);
    }

    std::shared_ptr<Texture> default_emissive_texture()
    {
        return single_color_texture(0.0f);
    }

    std::shared_ptr<Texture> default_mask_texture()
    {
        return single_color_texture(1.0f);
    }

    std::shared_ptr<Material> make_simple_material(const glm::vec3& diffuse, const glm::vec3& specular, float roughtness) noexcept
    {
        return std::make_shared<Material>(make_color_texture(diffuse), make_color_texture(specular), make_color_texture(glm::vec3(roughtness)), default_normal_texture(), make_black_texture());
    }

    std::shared_ptr<Material> make_emissive_material(const glm::vec3& color) noexcept
    {
        return std::make_shared<Material>(make_black_texture(), make_black_texture(), make_black_texture(), default_normal_texture(), make_color_texture(color));
    }

    std::shared_ptr<Material> make_emissive_material(const std::shared_ptr<Texture>& texture) noexcept
    {
        return std::make_shared<Material>(make_black_texture(), make_black_texture(), make_black_texture(), default_normal_texture(), texture);
    }

    Material::Material(const std::shared_ptr<Texture>& d, const std::shared_ptr<Texture>& s, const std::shared_ptr<Texture>& r)
    : Material(d, s, r, default_normal_texture(), default_emissive_texture(), default_mask_texture()) {}

    Material::Material(const std::shared_ptr<Texture>& d, const std::shared_ptr<Texture>& s, const std::shared_ptr<Texture>& r, const std::shared_ptr<Texture>& n)
    : Material(d, s, r, n, default_emissive_texture(), default_mask_texture()) {}

    Material::Material(const std::shared_ptr<Texture>& d, const std::shared_ptr<Texture>& s, const std::shared_ptr<Texture>& r, const std::shared_ptr<Texture>& n, const std::shared_ptr<Texture>& e)
    : Material(d, s, r, n, e, default_mask_texture()) {}

    Material::Material(const std::shared_ptr<Texture>& d, const std::shared_ptr<Texture>& s, const std::shared_ptr<Texture>& r, const std::shared_ptr<Texture>& n, const std::shared_ptr<Texture>& e, const std::shared_ptr<Texture>& m)
    : diffuse(d), specular(s), roughtness(r), normal(n), emissive(e), mask(m)
    {
        DBG_ASSERT(diffuse);
        DBG_ASSERT(specular);
        DBG_ASSERT(roughtness);
        DBG_ASSERT(normal);
        DBG_ASSERT(emissive);
        DBG_ASSERT(mask);
    }

    Material::Material(const std::filesystem::path& filename)
    {
        auto input = std::ifstream{filename};
        if (!input.is_open())
        {
            throw std::runtime_error(compose("Failed to open %0 for reading.", filename.u8string()));
        }
        auto jmn = nlohmann::json{};
        input >> jmn;

        auto dir = filename.parent_path();

        if (jmn.contains("diffuseMap"))
        {
            auto file = std::string(jmn["diffuseMap"]);
            diffuse = std::make_shared<Texture>(dir / file);
        }

        if (jmn.contains("specularMap"))
        {
            auto file = std::string(jmn["specularMap"]);
            specular = std::make_shared<Texture>(dir / file);
        }

        if (jmn.contains("roughtnessMap"))
        {
            auto file = std::string(jmn["roughtnessMap"]);
            roughtness = std::make_shared<Texture>(dir / file);
        }

        if (jmn.contains("normalMap"))
        {
            auto file = std::string(jmn["normalMap"]);
            normal = std::make_shared<Texture>(dir / file);
        }

        if (jmn.contains("emissiveMap"))
        {
            auto file = std::string(jmn["emissiveMap"]);
            emissive = std::make_shared<Texture>(dir / file);
        }
    }

    void Material::set_diffuse(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        diffuse = value;
    }

    const std::shared_ptr<Texture>& Material::get_diffuse() const noexcept
    {
        return diffuse;
    }

    void Material::set_specular(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        specular = value;
    }

    const std::shared_ptr<Texture>& Material::get_specular() const noexcept
    {
        return specular;
    }

    void Material::set_roughtness(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        roughtness = value;
    }

    const std::shared_ptr<Texture>& Material::get_roughtness() const noexcept
    {
        return roughtness;
    }

    void Material::set_normal(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        normal = value;
    }

    const std::shared_ptr<Texture>& Material::get_normal() const noexcept
    {
        return normal;
    }

    void Material::set_emissive(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        emissive = value;
    }

    const std::shared_ptr<Texture>& Material::get_emissive() const noexcept
    {
        return emissive;
    }

    void Material::set_mask(const std::shared_ptr<Texture>& value) noexcept
    {
        DBG_ASSERT(value);
        mask = value;
    }

    const std::shared_ptr<Texture>& Material::get_collision_mask() const noexcept
    {
        return mask;
    }

    std::shared_ptr<Parameters> Material::to_parameters() const noexcept
    {
        DBG_ASSERT(diffuse);
        DBG_ASSERT(specular);
        DBG_ASSERT(roughtness);
        DBG_ASSERT(normal);
        DBG_ASSERT(emissive);
        DBG_ASSERT(mask);

        auto params = std::make_shared<Parameters>();

        params->set_value("pkzo_DiffuseMap",    diffuse);
        params->set_value("pkzo_SpecularMap",   specular);
        params->set_value("pkzo_RoughtnessMap", roughtness);
        params->set_value("pkzo_NormalMap",     normal);
        params->set_value("pkzo_EmissiveMap",   emissive);
        params->set_value("pkzo_Mask",          mask);

        return params;
    }
}