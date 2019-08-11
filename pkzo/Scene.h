// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SCENE_H_
#define _PKZO_SCENE_H_

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "defines.h"
#include "stdex.h"

namespace pkzo
{
    class Engine;
    class SceneNode;
    class Camera;
    class FrameBuffer;
    class RenderQueue;

    /*!
     * 3d Stuff
     */
    class PKZO_EXPORT Scene : private stdex::non_copyable
    {
    public:
        virtual ~Scene();

        //! Get the scene's engine./
        Engine& get_engine();

        /*!
         * Add a node to the scene.
         *
         * @param node the node to add
         */
        void add_node(const std::shared_ptr<SceneNode>& node);

        /*!
         * Remove a node from the scene.
         *
         * @param node the node to remove
         */
        void remove_node(const std::shared_ptr<SceneNode>& node);

        template <typename NodeT>
        std::list<std::shared_ptr<NodeT>> get_nodes();

        /*!
         * Draw the scene.
         *
         * @param camera the camera to render from
         */
        void draw(const Camera& camera, RenderQueue& queue);

        //! Activate the scene.
        virtual void activate();
        //! Deactivate the scene.
        virtual void deactivate();
        //! Update the scene
        //! @param dt the duration from the last frame in seconds
        virtual void update(float dt);

    private:
        Engine* engine;
        std::list<std::shared_ptr<SceneNode>> nodes;

    friend class Engine;
    };

    template <typename NodeT>
    std::list<std::shared_ptr<NodeT>> Scene::get_nodes()
    {
        auto result = std::list<std::shared_ptr<NodeT>>();
        for (auto& node : nodes)
        {
            auto node_t = std::dynamic_pointer_cast<NodeT>(node);
            if (node_t)
            {
                result.push_back(node_t);
            }
        }
        return result;
    }
}

#endif
