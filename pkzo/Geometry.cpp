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
#include "Geometry.h"

#include "Scene.h"
#include "Renderer.h"

namespace pkzo
{
    Geometry::Geometry() = default;

    Geometry::Geometry(glm::mat4 transform, const std::shared_ptr<Material>& m)
    : SceneNode(transform), material(m) {}

    Geometry::Geometry(const Geometry& other)
    : SceneNode(other) {}

    Geometry::~Geometry() = default;

    void Geometry::serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const
    {
        SceneNode::serialize(j, base_dir);

        if (material)
        {
            auto diff = std::filesystem::relative(material->get_file(), base_dir);
            j["material"] = diff;
        }
    }

    void Geometry::deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir)
    {
        SceneNode::deserialize(j, base_dir);

        auto material_file = j.value("material", std::string{});
        if (!material_file.empty())
        {
            auto canoncial_path = std::filesystem::weakly_canonical(base_dir / material_file);
            material = std::make_shared<Material>(canoncial_path);
        }
    }

    void Geometry::activate()
    {
        attach_graphics();
    }

    void Geometry::deactivate()
    {
        auto scene = get_scene();
        check(scene != nullptr);

        auto& renderer = scene->get_renderer();
        renderer.remove_geometry(gid);
    }

    void Geometry::set_material(const std::shared_ptr<Material>& value)
    {
        material = value;

        if (get_scene() != nullptr)
        {
            sync_graphics();
        }
    }

    std::shared_ptr<Material> Geometry::get_material() const
    {
        return material;
    }
}
