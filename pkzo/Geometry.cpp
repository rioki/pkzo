// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Geometry.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"

namespace pkzo
{
    Geometry::Geometry() = default;
    Geometry::~Geometry() = default;

    void Geometry::set_mesh(std::shared_ptr<Mesh> value)
    {
        mesh = std::move(value);
    }

    std::shared_ptr<Mesh> Geometry::get_mesh() const
    {
        return mesh;
    }

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = std::move(value);
    }

    std::shared_ptr<Material> Geometry::get_material()
    {
        return material;
    }

    void Geometry::draw(const Camera& camera)
    {
        if (!mesh || !material)
        {
            return;
        }
        auto shader = material->get_shader();
        if (!shader)
        {
            return;
        }

        auto proj  = camera.get_projection();
        auto view  = camera.get_view();
        auto model = get_transform();

        shader->bind();
        shader->set_uniform("pkzo_ProjectionMatrix", proj);
        shader->set_uniform("pkzo_ViewMatrix", view);
        shader->set_uniform("pkzo_ModelMatrix", model);
        material->bind(*shader);
        mesh->bind(*shader);
        mesh->draw();
        mesh->unbind();
        material->unbind();
        shader->unbind();
    }
}
