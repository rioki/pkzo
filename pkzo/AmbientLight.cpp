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
#include "AmbientLight.h"

#include "Scene.h"
#include "Renderer.h"

namespace pkzo
{
    PKZO_THREE_REGISTER_TYPE(AmbientLight);

    AmbientLight::AmbientLight() = default;

    AmbientLight::AmbientLight(glm::vec3 c)
    : color(c) {}

    AmbientLight::AmbientLight(glm::mat4 transform, glm::vec3 c)
    : Light(transform), color(c) {}

    AmbientLight::AmbientLight(const AmbientLight& other)
    : Light(other), color(other.color) {}

    AmbientLight::~AmbientLight() = default;

    std::string AmbientLight::get_type() const noexcept
    {
        return "AmbientLight";
    }

    std::unique_ptr<SceneNode> AmbientLight::clone() const noexcept
    {
        return std::make_unique<AmbientLight>(*this);
    }

    void AmbientLight::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        Light::serialize(j, base_dir);
        j["color"] = color;
    }

    void AmbientLight::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        Light::deserialize(j, base_dir);
        color = j.value("color", color);
    }

    glm::vec3 AmbientLight::get_color() const
    {
        return color;
    }

    void AmbientLight::set_color(glm::vec3 value)
    {
        color = value;

        if (get_scene() != nullptr)
        {
            sync_graphics();
        }
    }

    void AmbientLight::attach_graphics()
    {
        auto scene = get_scene();
        check(scene);

        auto& renderer = scene->get_renderer();
        gid = renderer.add_ambient_light(color);
    }

    void AmbientLight::sync_graphics()
    {
        auto scene = get_scene();
        check(scene);

        auto& renderer = scene->get_renderer();
        renderer.remove_light(gid);
        gid = renderer.add_ambient_light(color);
    }
}
