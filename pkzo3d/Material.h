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

#pragma once

#include <filesystem>
#include <memory>

#include <glm/glm.hpp>

#include <pkzo/Texture.h>

#include "api.h"

namespace pkzo3d
{
    using pkzo::Texture;

    class PKZO3D_EXPORT Material
    {
    public:
        struct Props
        {
            float                    opacity_factor         = 1.0f;
            glm::vec3                base_color_factor      = glm::vec3(1.0f);
            std::shared_ptr<Texture> base_color_map         = nullptr;
            float                    roughness_factor       = 1.0f;
            float                    metallic_factor        = 0.0f;
            std::shared_ptr<Texture> metallic_roughness_map = nullptr;
            std::shared_ptr<Texture> normal_map             = nullptr;
            glm::vec3                emissive_factor        = glm::vec3(0.0f);
            std::shared_ptr<Texture> emissive_map           = nullptr;
        };

        static inline std::shared_ptr<Material> create(Props props)
        {
            return std::make_shared<Material>(std::move(props));
        }

        static inline std::shared_ptr<Material> load(const std::filesystem::path& file)
        {
            return std::make_shared<Material>(file);
        }

        Material(const std::filesystem::path& file);

        Material(Props init);

        ~Material();

        float get_opacity_factor() const;

        const glm::vec3& get_base_color_factor() const;

        std::shared_ptr<Texture> get_base_color_map() const;

        float get_roughness_factor() const;

        float get_metallic_factor() const;

        std::shared_ptr<Texture> get_metallic_roughness_map() const;

        std::shared_ptr<Texture> get_normal_map() const;

        const glm::vec3&get_emissive_factor() const;

        std::shared_ptr<Texture> get_emissive_map() const;

    private:
        float                    opacity_factor;
        glm::vec3                base_color_factor;
        std::shared_ptr<Texture> base_color_map;
        float                    roughness_factor;
        float                    metallic_factor;
        std::shared_ptr<Texture> metallic_roughness_map;
        std::shared_ptr<Texture> normal_map;
        glm::vec3                emissive_factor;
        std::shared_ptr<Texture> emissive_map;

        Material(const Material&) = delete;
        Material& operator = (const Material&) = delete;
    };
}