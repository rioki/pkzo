
#include "Scene.h"

#include <stdexcept>
#include <algorithm>

#include "SceneNode.h"
#include "SceneRenderer.h"

namespace pkzo
{
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::add_node(SceneNode& node)
    {
        nodes.push_back(&node);
    }

    void Scene::remove_node(SceneNode& node)
    {
        auto i = std::find(nodes.begin(), nodes.end(), &node);
        if (i == nodes.end())
        {
            throw std::logic_error("node not in scene");
        }
        nodes.erase(i);
    }

    void Scene::update(float t, float dt)
    {
        for (SceneNode* node : nodes)
        {
            node->update(t, dt);
        }
    }

    void Scene::render(SceneRenderer& renderer) const
    {
        for (const SceneNode* node : nodes)
        {
            node->enqueue(renderer);
        }

        renderer.render();
    }
}
