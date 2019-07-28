// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details._

#include "RenderQueue.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "dbg.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

namespace pkzo
{
    RenderQueue::RenderQueue()
    {
        rectangle_mesh = Mesh::create_rectangle({1.0f, 1.0f});
    }

    void RenderQueue::clear()
    {
        projection_matrix = glm::mat4(1.0f);
        view_matrix = glm::mat4(1.0f);
        geometry.clear();
    }

    void RenderQueue::set_othro_camera(float left, float right, float bottom, float top, float near, float far)
    {
        projection_matrix = glm::ortho(left, right, bottom, top, near, far);
        view_matrix = glm::mat4(1.0f);
    }

    void RenderQueue::submit_rectangle(const glm::mat4& model_matrix, const glm::vec2& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix)
    {
        geometry.push_back({glm::scale(model_matrix, glm::vec3(size, 1.0f)), texture_matrix, rectangle_mesh, material});
    }

    void RenderQueue::execute(BlendMode blend_mode)
    {
        switch (blend_mode)
        {
            case BlendMode::NONE:
                glDisable(GL_BLEND);
                break;
            case BlendMode::ALPHA:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case BlendMode::ADITIVE:
                glDisable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);
                break;
        }

        for (const auto& geom : geometry)
        {
            PKZO_ASSERT(geom.material);
            PKZO_ASSERT(geom.mesh);

            auto shader = geom.material->get_shader();
            PKZO_ASSERT(shader);

            shader->bind();
            shader->set_uniform("pkzo_ProjectionMatrix", projection_matrix);
            shader->set_uniform("pkzo_ViewMatrix", view_matrix);
            shader->set_uniform("pkzo_ModelMatrix", geom.model_matrix);
            shader->set_uniform("pkzo_TextureMatrix", geom.texture_matrix);
            geom.material->bind(*shader);
            geom.mesh->bind(*shader);
            geom.mesh->draw();
            geom.mesh->unbind();
            geom.material->unbind();
            shader->unbind();
        }
    }
}
