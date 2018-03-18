/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Scene.h"

#include <algorithm>

#include "SceneRenderer.h"
#include "Camera.h"

namespace pkzo
{
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::add_entity(Entity& entity)
    {
        entities.push_back(&entity);
    }

    void Scene::remove_entity(Entity& entity)
    {
        auto i = std::find(entities.begin(), entities.end(), &entity);
        if (i != entities.end())
        {
            entities.erase(i);
        }
        else
        {
            throw std::logic_error("entity no in scene");
        }
    }

    void Scene::draw(SceneRenderer& renderer, float aspect, const Camera& camera)
    {
        rgm::mat4 proj = camera.get_projection_matrix(aspect);
        rgm::mat4 view = camera.get_view_matrix();
        renderer.orient_camera(proj, view);

        for (Entity* entity : entities)
        {
            entity->enqueue(renderer, camera);
        }

        renderer.render();
    }
}
