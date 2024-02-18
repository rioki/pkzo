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

#pragma once

#include <memory>
#include <filesystem>

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <pkzo/Image.h>

#include "defines.h"

#ifdef OPAQUE
#undef OPAQUE
#endif

namespace pkzo
{
    enum class AlphaMode
    {
        OPAQUE,
        MASK,
        BLEND
    };

    PKZO_EXPORT std::ostream& operator << (std::ostream& os, const AlphaMode& mode);
    PKZO_EXPORT void to_json(nlohmann::json& j, const AlphaMode& mode);
    PKZO_EXPORT void from_json(const nlohmann::json& j, AlphaMode& mode);

    class PKZO_EXPORT Material
    {
    public:
        Material() = default;
        Material(const std::filesystem::path& file);
        ~Material() = default;

        Material(const Material&) = default;
        Material& operator = (const Material&) = default;

        Material(Material&&) = default;
        Material& operator = (Material&&) = default;

        bool operator == (const Material& other) const noexcept;

        std::filesystem::path get_file() const noexcept;

        void set_alpha_mode(AlphaMode mode) noexcept;
        AlphaMode get_alpha_mode() const noexcept;

        void set_base_color_factor(const glm::vec4& factor) noexcept;
        const glm::vec4& get_base_color_factor() const noexcept;

        void set_base_color_map(const std::shared_ptr<Image>& texture) noexcept;
        const std::shared_ptr<Image>& get_base_color_map() const noexcept;

        void set_metallic_factor(float factor) noexcept;
        float get_metallic_factor() const noexcept;

        void set_roughness_factor(float factor) noexcept;
        float get_roughness_factor() const noexcept;

        void set_metallic_roughness_map(const std::shared_ptr<Image>& texture) noexcept;
        const std::shared_ptr<Image>& get_metallic_roughness_map() const noexcept;

        void set_emissive_factor(const glm::vec3& factor) noexcept;
        const glm::vec3& get_emissive_factor() const noexcept;

        void set_emissive_map(const std::shared_ptr<Image>& texture) noexcept;
        const std::shared_ptr<Image>& get_emissive_map() const noexcept;

        void set_normal_map(const std::shared_ptr<Image>& texture) noexcept;
        const std::shared_ptr<Image>& get_normal_map() const noexcept;

        void save(const std::filesystem::path& file) const;

    private:
        std::filesystem::path file;
        AlphaMode alpha_mode = AlphaMode::OPAQUE;
        glm::vec4 base_color_factor = glm::vec4(1.0f);
        std::shared_ptr<Image> base_color_map;
        float metallic_factor = 1.0f;
        float roughness_factor = 1.0f;
        std::shared_ptr<Image> metallic_roughness_map;
        glm::vec3 emissive_factor = glm::vec3(0.0f);
        std::shared_ptr<Image> emissive_map;
        std::shared_ptr<Image> normal_map;
    };
}
