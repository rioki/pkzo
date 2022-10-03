// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "Scene.h"

#include "Engine.h"
#include "GraphicSystem.h"
#include "SceneRenderer.h"

namespace ice
{
    SceneRenderer* Scene::get_renderer() noexcept
    {
        return renderer;
    }

    const SceneRenderer* Scene::get_renderer() const noexcept
    {
        return renderer;
    }

    void Scene::draw() noexcept
    {
        if (renderer)
        {
            renderer->render();
        }
    }

    void Scene::activate()
    {
        auto engine = get_engine();
        assert(engine != nullptr);

        if (auto gs = engine->get_system<GraphicSystem>())
        {
            renderer = gs->create_scene_renderer();
        }

        NodeRoot<Scene>::activate();
    }

    void Scene::deactivate()
    {
        NodeRoot<Scene>::deactivate();

        if (renderer)
        {
            auto engine = get_engine();
            assert(engine != nullptr);

            auto gs = engine->get_system<GraphicSystem>();
            assert(gs);
            gs->release_scene_renderer(renderer);
            renderer = nullptr;
        }
    }
}
