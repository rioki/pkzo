// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Rectangle.h"

#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include <glm/gtc/matrix_transform.hpp>

namespace pkzo
{
    Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Material>& m)
    : ScreenNode(position, size),
      mesh(Mesh::create_rectangle(glm::vec2(1.0), true)),
      material(m) {}

    Rectangle::~Rectangle() = default;

    void Rectangle::set_material(const std::shared_ptr<Material>& value)
    {
        material = value;
    }

    const std::shared_ptr<Material>& Rectangle::get_material() const
    {
        return material;
    }

    void Rectangle::draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model)
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

        auto local_model = glm::translate(model, glm::vec3(get_position(), 0.0f));
        local_model = glm::scale(local_model, glm::vec3(get_size(), 1.0f));

        shader->bind();
        shader->set_uniform("pkzo_ProjectionMatrix", proj);
        shader->set_uniform("pkzo_ViewMatrix", view);
        shader->set_uniform("pkzo_ModelMatrix", local_model);
        material->bind(*shader);
        mesh->bind(*shader);
        mesh->draw();
        mesh->unbind();
        material->unbind();
        shader->unbind();
    }
}
