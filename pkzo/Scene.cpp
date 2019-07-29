// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Scene.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "dbg.h"
#include "SceneNode.h"
#include "Camera.h"
#include "RenderQueue.h"

namespace pkzo
{
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::add_node(const std::shared_ptr<SceneNode>& node)
    {
        PKZO_ASSERT(node->scene == nullptr);
        nodes.push_back(node);
        node->scene = this;
    }

    void Scene::remove_node(const std::shared_ptr<SceneNode>& node)
    {
        PKZO_ASSERT(node->scene == this);
        auto i = std::find(nodes.begin(), nodes.end(), node);
        if (i == nodes.end())
        {
            PKZO_THROW(std::invalid_argument, "Node is not in scene.``");
        }
        node->scene = nullptr;
        nodes.erase(i);
    }

    void Scene::draw(const Camera& camera, RenderQueue& queue)
    {
        PKZO_ASSERT(this == &camera.get_scene());

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        queue.clear();
        camera.setup(queue);

        for (auto& node : nodes)
        {
            node->enqueue(queue);
        }

        queue.execute(RenderAlgorithm::LIT_FORWARD);
    }
}