// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details._

#include "pch.h"
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
    RenderQueue::RenderQueue(const glm::uvec2& r)
    : resolution(r)
    {
        rectangle_mesh = Mesh::create_rectangle({1.0f, 1.0f});
        box_mesh = Mesh::create_box({1.0f, 1.0f, 1.0f});
    }

    void RenderQueue::clear()
    {
        projection_matrix = glm::mat4(1.0f);
        view_matrix = glm::mat4(1.0f);
        geometry.clear();
        lights.clear();
    }

    void RenderQueue::set_resolution(const glm::uvec2& value)
    {
        resolution = value;
    }

    void RenderQueue::set_othro_camera(float left, float right, float bottom, float top, float near, float far)
    {
        projection_matrix = glm::ortho(left, right, bottom, top, near, far);
        view_matrix = glm::mat4(1.0f);
    }

    void RenderQueue::set_perspective_camera(const glm::mat4& transform, float fov)
    {
        auto distance = 1000.0f; // TOOD determine the render distance from the geometry

        auto aspect = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        auto fovy = glm::radians(fov) / aspect;
        projection_matrix = glm::perspective(fovy / 2.0f, fovy, 0.1f, distance);

        auto eye      = glm::vec3(transform[3]);
        auto rotation = glm::mat3(transform);
        auto forward  = glm::vec3(rotation * glm::vec3(0.0f, 0.0f, -1.0f));
        auto up       = glm::vec3(rotation * glm::vec3(0.0f, 1.0f, 0.0f));
        auto target   = eye + forward;
        view_matrix   = glm::lookAt(eye, target, up);
    }

    void RenderQueue::submit_rectangle(const glm::mat4& model_matrix, const glm::vec2& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix)
    {
        geometry.push_back({glm::scale(model_matrix, glm::vec3(size, 1.0f)), texture_matrix, rectangle_mesh, material});
    }

    void RenderQueue::submit_box(const glm::mat4& model_matrix, const glm::vec3& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix)
    {
        geometry.push_back({glm::scale(model_matrix, size), texture_matrix, box_mesh, material});
    }

    void RenderQueue::submit_mesh(const glm::mat4& model_matrix, std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix)
    {
        geometry.push_back({model_matrix, texture_matrix, mesh, material});
    }

    void RenderQueue::submit_ambient_light(const glm::vec3& color)
    {
        lights.push_back({AMBIENT_LIGHT, color});
    }

    void RenderQueue::submit_directional_light(const glm::vec3& color, const glm::vec3& direction)
    {
        lights.push_back({DIRECTIONAL_LIGHT, color, glm::vec3(0.0f), direction});
    }

    void RenderQueue::submit_point_light(const glm::vec3& color, const glm::vec3& position)
    {
        lights.push_back({POINT_LIGHT, color, position});
    }

    void RenderQueue::submit_spot_light(const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction, float angle)
    {
        lights.push_back({SPOT_LIGHT, color, position, direction, angle});
    }

    void RenderQueue::execute(RenderAlgorithm algorithm)
    {
        // TODO reverse Z
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        switch (algorithm)
        {
            case RenderAlgorithm::UNLIT:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case RenderAlgorithm::LIT_FORWARD:
            case RenderAlgorithm::LIT_DEFERRED:
                glDisable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);
                break;
        }

        switch (algorithm)
        {
            case RenderAlgorithm::UNLIT:
            case RenderAlgorithm::LIT_DEFERRED:
                draw_unlit_geometry();
                break;
            case RenderAlgorithm::LIT_FORWARD:
                draw_lit_geometry();
                break;
        }

    }

    void RenderQueue::draw_unlit_geometry()
    {
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

    void RenderQueue::draw_lit_geometry()
    {
        for (const auto& geom : geometry)
        {
            PKZO_ASSERT(geom.material);
            PKZO_ASSERT(geom.mesh);

            glDisable(GL_BLEND);

            auto shader = geom.material->get_shader();
            PKZO_ASSERT(shader);

            shader->bind();
            shader->set_uniform("pkzo_ProjectionMatrix", projection_matrix);
            shader->set_uniform("pkzo_ViewMatrix", view_matrix);
            shader->set_uniform("pkzo_ModelMatrix", geom.model_matrix);
            shader->set_uniform("pkzo_TextureMatrix", geom.texture_matrix);
            geom.material->bind(*shader);
            geom.mesh->bind(*shader);

            for (const auto& light : lights)
            {
                shader->set_uniform("pkzo_LightType", light.type);
                shader->set_uniform("pkzo_LightColor", light.color);
                shader->set_uniform("pkzo_LightPosition", light.position);
                shader->set_uniform("pkzo_LightDirection", light.direction);
                shader->set_uniform("pkzo_LightAngle", light.angle);

                geom.mesh->draw();

                glEnable(GL_BLEND);
            }

            geom.mesh->unbind();
            geom.material->unbind();
            shader->unbind();
        }
    }
}
