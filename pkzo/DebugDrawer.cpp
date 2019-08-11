// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "DebugDrawer.h"

#include <GL/glew.h>

#include "resource.h"
#include "Engine.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

namespace pkzo
{
    std::unique_ptr<Mesh> create_line(glm::vec3 start, glm::vec3 end)
    {
        auto mesh = std::make_unique<Mesh>();

        mesh->set_vertex_count(2u);

        mesh->set_vertex(0u, start);
        mesh->set_vertex(1u, end);

        mesh->set_texcoord(0u, {0.0f, 0.0f});
        mesh->set_texcoord(1u, {1.0f, 0.0f});

        auto dir = glm::normalize(end - start);
        mesh->set_tangent(0u, dir);
        mesh->set_tangent(1u, dir);

        auto t = glm::normalize(glm::cross(dir, glm::vec3{0.0f, 0.0f, 1.0f}));
        auto normal = glm::normalize(glm::cross(dir, t));
        mesh->set_tangent(0u, normal);
        mesh->set_tangent(1u, normal);

        mesh->set_line_count(1u);
        mesh->set_line(0u, {0u, 1u});

        return mesh;
    }

    DebugDrawer::DebugDrawer(Engine& e)
    : engine(e)
    {
        // TODO use common asset repository
        line_shader = std::make_unique<Shader>(ID_GLSL_DEBUG_LINE);
        line_mesh = create_line({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f});
    }

    void DebugDrawer::draw_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {
        draw_line(start, end, color, color);
    }

    void DebugDrawer::draw_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color)
    {
        lines.push({start, end, start_color, end_color});
    }

    void DebugDrawer::tick(float dt)
    {
        // do nothing
    }

    void DebugDrawer::draw(Camera& camera)
    {
        auto& window = engine.get_window();
        projection = camera.get_projection_matrix(window.get_aspect(), 1000.0f);
        model_view = camera.get_view_matrix();

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        line_shader->bind();
        line_mesh->bind(*line_shader);

        line_shader->set_uniform("pkzo_ProjectionMatrix", projection);
        line_shader->set_uniform("pkzo_ViewMatrix", model_view);

        while (!lines.empty())
        {
            auto line = lines.front();

            line_shader->set_uniform("uStart", line.start);
            line_shader->set_uniform("uEnd", line.end);
            line_shader->set_uniform("uStartColor", line.start_color);
            line_shader->set_uniform("uEndColor", line.end_color);
            line_mesh->draw();

            lines.pop();
        }

        line_mesh->unbind();
        line_shader->unbind();
    }
}
