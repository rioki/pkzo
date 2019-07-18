// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Light.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"
#include "FrameBuffer.h"

namespace pkzo
{
    Light::Light() = default;
    Light::~Light() = default;

    void Light::set_mesh(std::shared_ptr<Mesh> value)
    {
        mesh = std::move(value);
    }

    std::shared_ptr<Mesh> Light::get_mesh() const
    {
        return mesh;
    }

    void Light::set_material(std::shared_ptr<Material> value)
    {
        material = std::move(value);
    }

    std::shared_ptr<Material> Light::get_material()
    {
        return material;
    }

    void Light::draw(const Camera& camera, FrameBuffer& target)
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
        target.bind_inputs(*shader);
        material->bind(*shader);
        mesh->bind(*shader);
        mesh->draw();
        mesh->unbind();
        material->unbind();
        shader->unbind();
    }
}
