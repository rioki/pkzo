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
#include "Actor.h"

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
        // NOTE: emissive should be a MULTIPASS blend mode, but until transparancy is implemented in a seperate pass, it needs to be ALPHA for UI elements.
        render_pipeline->add_pass(PassType::GEOMETRY, load_shader(hModule, IDR_GLSL_EMISSIVE_VERT, IDR_GLSL_EMISSIVE_FRAG), DepthTest::ON, Blending::ALPHA);

        return render_pipeline;
    }

    Scene::Scene()
    : Scene(physics::World::create()) {}

    Scene::Scene(std::shared_ptr<physics::World> p)
    : physics(p)
    {
        render_pipeline = create_phong_pipeline();
    }

    Scene::~Scene() = default;

    Pipeline* Scene::get_render_pipeline() noexcept
    {
        return render_pipeline.get();
    }

    const Pipeline* Scene::get_render_pipeline() const noexcept
    {
        return render_pipeline.get();
    }

    void Scene::add_node(std::shared_ptr<SceneNode> child) noexcept
    {
        SceneNodeGroup::add_node(child);
        child->on_attach_scene(this);
    }

    void Scene::remove_node(std::shared_ptr<SceneNode> child) noexcept
    {
        child->on_detach_scene();
        SceneNodeGroup::remove_node(child);
    }

    void Scene::update(std::chrono::milliseconds dt) noexcept
    {
        physics->update(dt);
        SceneNodeGroup::update(dt);
    }

    void Scene::draw(const Camera& camera) const noexcept
    {
        render_pipeline->set_camera(camera.get_projection(), camera.get_view());
        render_pipeline->execute();
    }

    void Scene::set_gravity(const glm::vec3& value) noexcept
    {
        assert(physics);
        physics->set_gravity(value);
    }

    glm::vec3 Scene::get_gravity() const noexcept
    {
        assert(physics);
        return physics->get_gravity();
    }

    std::shared_ptr<physics::World> Scene::get_physics() noexcept
    {
        assert(physics);
        return physics;
    }

    std::shared_ptr<const physics::World> Scene::get_physics() const noexcept
    {
        assert(physics);
        return physics;
    }

    std::optional<TestResult> Scene::test_ray(const glm::vec3& start, const glm::vec3& end) const noexcept
    {
        assert(physics);
        auto r = physics->test_ray(start, end);
        if (r.has_value())
        {
            auto node = std::any_cast<SceneNode*>(r->body->get_user_data());
            assert(node);
            return TestResult{node->shared_from_this(), r->position, r->normal};
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<TestResult> Scene::test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const noexcept
    {
        assert(physics);
        auto r = physics->test_sphere_sweep(start, end, radius);
        if (r.has_value())
        {
            auto node = std::any_cast<SceneNode*>(r->body->get_user_data());
            assert(node);
            return TestResult{node->shared_from_this(), r->position, r->normal};
        }
        else
        {
            return std::nullopt;
        }
    }

    void Scene::register_actor(Actor* actor)
    {
        actors.push_back(actor);
    }

    void Scene::unregister_actor(Actor* actor)
    {
        auto i = std::find(begin(actors), end(actors), actor);
        DBG_ASSERT(i != end(actors));
        actors.erase(i);
    }

    void Scene::handle_key_press(Key key, KeyMod mod) noexcept
    {
        for (auto& actor : actors)
        {
            actor->handle_key_press(key, mod);
        }
    }

    void Scene::handle_key_release(Key key, KeyMod mod) noexcept
    {
        for (auto& actor : actors)
        {
            actor->handle_key_release(key, mod);
        }
    }

    void Scene::handle_mouse_move(glm::vec2 pos, glm::vec2 rel) noexcept
    {
        for (auto& actor : actors)
        {
            actor->handle_mouse_move(pos, rel);
        }
    }

    void Scene::handle_mouse_press(MouseButton button, glm::vec2 pos) noexcept
    {
        for (auto& actor : actors)
        {
            actor->handle_mouse_press(button, pos);
        }
    }

    void Scene::handle_mouse_release(MouseButton button, glm::vec2 pos) noexcept
    {
        for (auto& actor : actors)
        {
            actor->handle_mouse_release(button, pos);
        }
    }
}