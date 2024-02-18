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
#include "DirectionalLight.h"

#include "Scene.h"
#include "Renderer.h"

namespace pkzo
{
    PKZO_THREE_REGISTER_TYPE(DirectionalLight);

    DirectionalLight::DirectionalLight() = default;

    DirectionalLight::DirectionalLight(glm::mat4 transform, glm::vec3 c)
    : Light(transform), color(c) {}

    DirectionalLight::DirectionalLight(const DirectionalLight& other)
    : Light(other), color(other.color) {}

    DirectionalLight::~DirectionalLight() = default;

    std::string DirectionalLight::get_type() const noexcept
    {
        return "DirectionalLight";
    }

    std::unique_ptr<SceneNode> DirectionalLight::clone() const noexcept
    {
        return std::make_unique<DirectionalLight>(*this);
    }

    void DirectionalLight::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        Light::serialize(j, base_dir);
        j["color"] = color;
    }

    void DirectionalLight::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        Light::deserialize(j, base_dir);
        color = j.value("color", color);
    }

    glm::vec3 DirectionalLight::get_color() const
    {
        return color;
    }

    void DirectionalLight::set_color(glm::vec3 value)
    {
        color = value;
    }

    void DirectionalLight::attach_graphics()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();

        auto dir = glm::mat3(get_global_transform()) * glm::vec3(0.0f, 0.0f, -1.0f);
        gid = renderer.add_directional_light(color, dir);
    }

    void DirectionalLight::sync_graphics()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();
        renderer.remove_light(gid);

        auto dir = glm::mat3(get_global_transform()) * glm::vec3(0.0f, 0.0f, -1.0f);
        gid = renderer.add_directional_light(color, dir);
    }
}
