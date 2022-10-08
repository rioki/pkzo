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

#pragma once
#include "config.h"

#include "Asset.h"

namespace ice
{
    class Texture;

    class ICE_EXPORT Material : public Asset
    {
    public:
        Material() noexcept = default;

        void set_base_color_factor(const glm::vec4& value) noexcept;
        const glm::vec4& get_base_color_factor() const noexcept;

        void set_base_color_map(const std::shared_ptr<ice::Texture>& value) noexcept;
        const std::shared_ptr<ice::Texture>& get_base_color_map() const noexcept;

        void set_emissive_factor(const glm::vec3& value) noexcept;
        const glm::vec3& get_emissive_factor() const noexcept;

        void set_emissive_map(const std::shared_ptr<ice::Texture>& value) noexcept;
        const std::shared_ptr<ice::Texture>& get_emissive_map() const noexcept;

    private:
        glm::vec4                     base_color_factor = glm::vec4(1.0f);
        std::shared_ptr<ice::Texture> base_color_map;
        glm::vec3                     emissive_factor   = glm::vec3(0.0f);
        std::shared_ptr<ice::Texture> emissive_map;
    };

    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec3& factor) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec3& factor, const std::shared_ptr<ice::Texture>& map) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec4& factor) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const std::shared_ptr<ice::Texture>& map) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_simple_material(const glm::vec4& factor, const std::shared_ptr<ice::Texture>& map) noexcept;

    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const glm::vec3& factor) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const std::shared_ptr<ice::Texture>& map) noexcept;
    ICE_EXPORT std::shared_ptr<Material> make_emissive_material(const glm::vec3& factor, const std::shared_ptr<ice::Texture>& map) noexcept;
}
