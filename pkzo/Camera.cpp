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
#include "Camera.h"

#include "Scene.h"
#include "Renderer.h"

namespace pkzo
{
    PKZO_THREE_REGISTER_TYPE(Camera);

    Camera::Camera() = default;

    Camera::Camera(glm::mat4 transform, float f)
    : SceneNode(transform), fov(f)  {}

    Camera::Camera(const Camera& other)
    : SceneNode(other), fov(other.fov) {}

    Camera::~Camera() = default;

    std::string Camera::get_type() const noexcept
    {
        return "Camera";
    }

    std::unique_ptr<SceneNode> Camera::clone() const noexcept
    {
        return std::make_unique<Camera>(*this);
    }

    void Camera::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        SceneNode::serialize(j, base_dir);
        j["fov"] = fov;
    }

    void Camera::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        SceneNode::deserialize(j, base_dir);
        fov = j.value("fov", fov);
    }

    void Camera::activate()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();

        renderer.set_camera(get_global_transform(), fov);
    }

    void Camera::deactivate()
    {
        // nothing to do
    }

    void Camera::update(float dt)
    {
        // TODO track movement events
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();

        renderer.set_camera(get_global_transform(), fov);
    }

    float Camera::get_fov() const noexcept
    {
        return fov;
    }

    void Camera::set_fov(float value) noexcept
    {
        fov = value;
    }
}
