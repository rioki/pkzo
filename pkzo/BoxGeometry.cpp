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
#include "BoxGeometry.h"

#include "Scene.h"
#include "Renderer.h"

namespace pkzo
{
    PKZO_THREE_REGISTER_TYPE(BoxGeometry);

    BoxGeometry::BoxGeometry() = default;

    BoxGeometry::BoxGeometry(glm::mat4 transform, glm::vec3 size, const std::shared_ptr<Material>& material)\
    : Geometry(transform, material), size(size) {}

    BoxGeometry::BoxGeometry(const BoxGeometry& other)
    : Geometry(other), size(other.size) {}

    BoxGeometry::~BoxGeometry() = default;

    std::string BoxGeometry::get_type() const noexcept
    {
        return "BoxGeometry";
    }

    std::unique_ptr<SceneNode> BoxGeometry::clone() const noexcept
    {
        return std::make_unique<BoxGeometry>(*this);
    }

    void BoxGeometry::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        Geometry::serialize(j, base_dir);
        j["size"] = size;
    }

    void BoxGeometry::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        Geometry::deserialize(j, base_dir);
        size = j.value("size", size);
    }

    glm::vec3 BoxGeometry::get_size() const noexcept
    {
        return size;
    }

    void BoxGeometry::set_size(glm::vec3 value) noexcept
    {
        size = value;

        if (get_scene() != nullptr)
        {
            sync_graphics();
        }
    }

    void BoxGeometry::attach_graphics()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();
        gid = renderer.add_box_geometry(get_global_transform(), size, get_material());
    }

    void BoxGeometry::sync_graphics()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();
        renderer.remove_geometry(gid);
        gid = renderer.add_box_geometry(get_global_transform(), size, get_material());
    }
}
