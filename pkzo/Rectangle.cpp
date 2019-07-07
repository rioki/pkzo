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
    std::shared_ptr<Mesh> make_uniform_rect()
    {
        auto mesh = std::make_shared<Mesh>();
        mesh->set_vertex_count(4u);

        mesh->set_vertex(0u, glm::vec3( 0.5f,  0.5f, 0.0f));
        mesh->set_vertex(1u, glm::vec3( 0.5f, -0.5f, 0.0f));
        mesh->set_vertex(2u, glm::vec3(-0.5f, -0.5f, 0.0f));
        mesh->set_vertex(3u, glm::vec3(-0.5f,  0.5f, 0.0f));

        mesh->set_normal(0u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(1u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(2u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(3u, glm::vec3(0.0f, 0.0f, 1.0f));

        mesh->set_texcoord(0u, glm::vec2(1.0f, 0.0f));
        mesh->set_texcoord(1u, glm::vec2(1.0f, 1.0f));
        mesh->set_texcoord(2u, glm::vec2(0.0f, 1.0f));
        mesh->set_texcoord(3u, glm::vec2(0.0f, 0.0f));

        mesh->set_tangent(0u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(1u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(2u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(3u, glm::vec3(1.0f, 0.0f, 0.0f));

        mesh->set_face_count(2u);
        mesh->set_face(0u, 0u, 1u, 2u);
        mesh->set_face(1u, 2u, 3u, 0u);

        return mesh;
    }

    Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Material>& m)
    : ScreenNode(position, size),
      mesh(make_uniform_rect()),
      material(m) {}

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
