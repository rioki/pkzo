// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Scene.h"

#include <pkzo/debug.h>

#include "SceneRenderer.h"
#include "PhysicsSimulation.h"

namespace pkzo
{
    using pkzo::check;

    Scene::Scene() = default;

    Scene::~Scene()
    {
        remove_all_children();
    }

    SceneRenderer* Scene::get_renderer()
    {
        if (!renderer)
        {
            renderer = std::make_unique<SceneRenderer>();
        }
        return renderer.get();
    }

    const SceneRenderer* Scene::get_renderer() const
    {
        return renderer.get();
    }

    PhysicsSimulation* Scene::get_physics_simulation()
    {
        if (!physics_simulation)
        {
            physics_simulation = PhysicsSimulation::create();
        }
        return physics_simulation.get();
    }

    const PhysicsSimulation* Scene::get_physics_simulation() const
    {
        return physics_simulation.get();
    }

    void Scene::enable_physics_debug()
    {
        auto phys = get_physics_simulation();
        auto rend = get_renderer();

        phys->enable_debug_render(*rend);
    }

    void Scene::disable_physics_debug()
    {
        auto phys = get_physics_simulation();
        phys->disable_debug_render();
    }

    void Scene::set_gravity(const glm::vec3& value)
    {
        auto ps = get_physics_simulation();
        check(ps);
        ps->set_gravity(value);
    }

    glm::vec3 Scene::get_gravity() const
    {
        auto ps = get_physics_simulation();
        if (ps)
        {
            return ps->get_gravity();
        }
        return glm::vec3(0.0f);
    }

    std::optional<TestResult> Scene::test_ray(const glm::vec3& start, const glm::vec3& end) const
    {
        if (physics_simulation)
        {
            return physics_simulation->test_ray(start, end);
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<TestResult> Scene::test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const
    {
        if (physics_simulation)
        {
            return physics_simulation->test_sphere_sweep(start, end, radius);
        }
        else
        {
            return std::nullopt;
        }
    }

    void Scene::update(float dt)
    {
        if (physics_simulation)
        {
            physics_simulation->update(dt);
        }

        Group::update(dt);
    }

    void Scene::draw(pkzo::GraphicContext& gc)
    {
        if (renderer)
        {
            renderer->render(gc);
        }
    }
}
