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

#include <pkzo/config.h>
#include <pkzo/Parameters.h>
#include <glm/glm.hpp>

namespace pkzo::three
{
    using FloatValue = std::variant<float, std::shared_ptr<Texture>>;
    using Vec3Value  = std::variant<glm::vec3, std::shared_ptr<Texture>>;

    //! Material
    class PKZO_EXPORT Material
    {
    public:

        void set_base_color_factor(const glm::vec3& value) noexcept;
        const glm::vec3& get_base_color_factor() const noexcept;

        void set_base_color_map(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_base_color_map() const noexcept;

        void set_roughness_factor(float value) noexcept;
        float get_roughness_factor() const noexcept;

        void set_metallic_factor(float value) noexcept;
        float get_metallic_factor() const noexcept;

        void set_metallic_roughtness_map(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_metallic_roughtness_map() const noexcept;

        void set_normal_map(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_normal_map() const noexcept;

        void set_emissive_factor(const glm::vec3& value) noexcept;
        const glm::vec3& get_emissive_factor() const noexcept;

        void set_emissive_map(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_emissive_map() const noexcept;

        std::shared_ptr<Parameters> to_parameters() const noexcept;

    private:
        glm::vec3                base_color_factor = glm::vec3(1.0f);
        std::shared_ptr<Texture> base_color_map;
        float                    roughness_factor = 0.5f;
        float                    metallic_factor = 0.0f;
        std::shared_ptr<Texture> metallic_roughtness_map;
        std::shared_ptr<Texture> normal_map;
        glm::vec3                emissive_factor = glm::vec3(0.0f);
        std::shared_ptr<Texture> emissive_map;
    };
}