//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
#include "Scene.h"

#include "resource.h"
#include "utils.h"
#include "Pipeline.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

namespace pkzo
{
    auto load_shader(HMODULE hModule, unsigned int vertex_id, unsigned int fragment_id)
    {
        auto vertex_code   = LoadTextResource(hModule, MAKEINTRESOURCE(vertex_id), _T("GLSL"));
        auto fragment_code = LoadTextResource(hModule, MAKEINTRESOURCE(fragment_id), _T("GLSL"));
        return std::make_shared<Shader>(vertex_code, fragment_code);
    }

    auto create_phong_pipeline()
    {
        HMODULE hModule = GetModuleHandle(_T("pkzo.dll"));

        auto render_pipeline = std::make_unique<Pipeline>();
        render_pipeline->add_pass(PassType::GEOMETRY_AND_LIGHTS, load_shader(hModule, IDR_GLSL_PHONG_VERT, IDR_GLSL_PHONG_FRAG));

        return render_pipeline;
    }

    Scene::Scene()
    {
        render_pipeline = create_phong_pipeline();
    }

    Pipeline* Scene::get_render_pipeline() noexcept
    {
        return render_pipeline.get();
    }

    const Pipeline* Scene::get_render_pipeline() const noexcept
    {
        return render_pipeline.get();
    }

    void Scene::add_child(std::shared_ptr<SceneNode> child) noexcept
    {
        SceneNodeGroup::add_child(child);
        child->on_attach_scene(this);
    }

    void Scene::remove_child(std::shared_ptr<SceneNode> child) noexcept
    {
        child->on_detach_scene();
        SceneNodeGroup::remove_child(child);
    }

    void Scene::draw(Camera& camera)
    {
        render_pipeline->set_camera(camera.get_projection(), camera.get_view());
        render_pipeline->execute();
    }
}