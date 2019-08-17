// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SCENE_NODE_H_
#define _PKZO_SCENE_NODE_H_

#include "defines.h"

#include <glm/glm.hpp>

#include "stdex.h"

namespace pkzo
{
    class Engine;
    class Scene;
    class RenderQueue;

    //! Node in the Scene
    class PKZO_EXPORT SceneNode : private stdex::non_copyable
    {
    public:
        virtual ~SceneNode();

        //! Get the node's engine.
        Engine& get_engine();
        //! Get the node's scene.
        Scene& get_scene();
        //! Get the node's scene.
        const Scene& get_scene() const;

        //! Get the node's parent.
        SceneNode* get_parent();
        const SceneNode* get_parent() const;

        //! Set the node's transform.
        void set_transform(const glm::mat4& value);

        //! Get the node's transform.
        const glm::mat4& get_transform() const;

        //! Get the node's world transform.
        glm::mat4 get_world_transform() const;

        //! Move the node by a given amount.
        void move(const glm::vec3& value);

        //! Rotate the node by a given amount.
        void rotate(float angle, const glm::vec3& axis);

        //! Submit draw commands to the render queue.
        virtual void enqueue(RenderQueue& queue) const;

        //! Activate the scene node.
        virtual void activate();
        //! Deactivate the scene node.
        virtual void deactivate();
        //! Update the scene.
        virtual void update(float dt);

    private:
        Scene*     scene     = nullptr;
        SceneNode* parent    = nullptr;
        glm::mat4  transform = glm::mat4(1.0f);

    friend class Scene;
    friend class SceneNodeGroup;
    };
}

#endif
