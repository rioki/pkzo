//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Pipeline.h"

#include "Shader.h"
#include "Mesh.h"
#include "Parameters.h"

namespace pkzo
{
    std::unique_ptr<Mesh> make_fullscreen_rectangle()
    {
        auto mesh = std::make_unique<Mesh>();

        mesh->add_vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f});

        mesh->add_triangle({0, 1, 2});
        mesh->add_triangle({2, 3, 0});

        return mesh;
    }

    Pipeline::Pipeline() noexcept
    : fullscreen_rectangle(make_fullscreen_rectangle()) {}

    void Pipeline::add_pass(PassType type, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Parameters>& parameters) noexcept
    {
        DBG_ASSERT(shader);
        DBG_ASSERT(parameters);
        passes.push_back({type, shader, parameters});
    }

    void Pipeline::set_camera(const glm::mat4& projection, const glm::mat4& view) noexcept
    {
        projection_matrix = projection;
        view_matrix = view;
    }

    unsigned int Pipeline::add_geometry(const glm::mat4& transform, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Parameters>& parameters) noexcept
    {
        DBG_ASSERT(mesh);
        DBG_ASSERT(parameters);
        last_geom_id++;
        geoms[last_geom_id] = {transform, mesh, parameters};
        return last_geom_id;
    }

    void Pipeline::update_geometry(unsigned int id, const glm::mat4& transform) noexcept
    {
        auto i = geoms.find(id);
        DBG_ASSERT(i != end(geoms));
        i->second.transform = transform;
    }

    void Pipeline::update_geometry(unsigned int id, const std::shared_ptr<Mesh>& mesh) noexcept
    {
        auto i = geoms.find(id);
        DBG_ASSERT(i != end(geoms));
        i->second.mesh = mesh;
    }

    void Pipeline::update_geometry(unsigned int id, const std::shared_ptr<Parameters>& parameters) noexcept
    {
        auto i = geoms.find(id);
        DBG_ASSERT(i != end(geoms));
        i->second.parameters = parameters;
    }

    void Pipeline::remove_geometry(unsigned int id) noexcept
    {
        auto i = geoms.find(id);
        DBG_ASSERT(i != end(geoms));
        geoms.erase(i);
    }

    void Pipeline::remove_all_geometry() noexcept
    {
        last_geom_id = 0;
        geoms.clear();
    }

    unsigned int Pipeline::add_light(const std::shared_ptr<Parameters>& parameters) noexcept
    {
        last_light_id++;
        lights[last_light_id] = {parameters};
        return last_light_id;
    }

    void Pipeline::update_light(unsigned int id, const std::shared_ptr<Parameters>& parameters) noexcept
    {
        auto i = lights.find(id);
        DBG_ASSERT(i != end(lights));
        i->second.parameters = parameters;
    }

    void Pipeline::remove_light(unsigned int id) noexcept
    {
        auto i = lights.find(id);
        DBG_ASSERT(i != end(lights));
        lights.erase(i);
    }

    void Pipeline::remove_all_light() noexcept
    {
        last_light_id = 0;
        lights.clear();
    }

    void apply(Shader& shader, Pipeline::Light& light) noexcept
    {
        DBG_ASSERT(light.parameters);
        apply(shader, *light.parameters);
    }

    void apply(Shader& shader, Pipeline::Geometry& geom) noexcept
    {
        shader.set_uniform("pkzo_ModelMatrix", geom.transform);
        DBG_ASSERT(geom.parameters);
        apply(shader, *geom.parameters);
    }

    void Pipeline::execute() noexcept
    {
        for (auto& pass : passes)
        {
            pass.shader->bind();
            pass.shader->set_uniform("pkzo_ProjectionMatrix", projection_matrix);
            pass.shader->set_uniform("pkzo_ViewMatrix",       view_matrix);
            apply(*pass.shader, *pass.parameters);
            switch (pass.type)
            {
            case PassType::FULLSCREEN:
                fullscreen_rectangle->bind(*pass.shader);
                fullscreen_rectangle->draw();
                break;
            case PassType::GEOMETRY:
                for (auto& [id, geom] : geoms)
                {
                    apply(*pass.shader, geom);
                    geom.mesh->bind(*pass.shader);
                    geom.mesh->draw();
                }
                break;
            case PassType::LIGHTS:
                for (auto& [id, light] : lights)
                {
                    apply(*pass.shader, light);
                    fullscreen_rectangle->bind(*pass.shader);
                    fullscreen_rectangle->draw();
                }
                break;
            case PassType::LIGHTS_AND_GEOMETRY:
                for (auto& [id, light] : lights)
                {
                    apply(*pass.shader, light);
                    for (auto& [id, geom] : geoms)
                    {
                        apply(*pass.shader, geom);
                        geom.mesh->bind(*pass.shader);
                        geom.mesh->draw();
                    }
                }
                break;
            case PassType::GEOMETRY_AND_LIGHTS:
                for (auto& [id, geom] : geoms)
                {
                    apply(*pass.shader, geom);
                    geom.mesh->bind(*pass.shader);
                    for (auto& [id, light] : lights)
                    {
                        apply(*pass.shader, light);
                        geom.mesh->draw();
                    }
                }
                break;
            }
        }
    }
}
