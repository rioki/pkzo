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

#include <glm/glm.hpp>

#include "defines.h"
#include "Light.h"

namespace pkzo
{
    class PKZO_EXPORT DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(glm::mat4 transform, glm::vec3 color);
        DirectionalLight(const DirectionalLight& other);
        ~DirectionalLight();

        std::string get_type() const noexcept override;
        std::unique_ptr<SceneNode> clone() const noexcept override;
        void serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const override;
        void deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir) override;

        glm::vec3 get_color() const;
        void set_color(glm::vec3 value);

    protected:
        void attach_graphics() override;
        void sync_graphics() override;

    private:
        glm::vec3 color = glm::vec3(1.0f);
    };
}
