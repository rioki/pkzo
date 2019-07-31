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
    class Scene;
    class RenderQueue;

    //! Node in the Scene
    class PKZO_EXPORT SceneNode : private stdex::non_copyable
    {
    public:
        SceneNode();
        virtual ~SceneNode();

        /*!
         * Get the node's scene.
         *
         * @return the node's scene.
         */
        Scene& get_scene();
        const Scene& get_scene() const;
        /*! @} */

        /*!
         * Set the node's transform.
         *
         * @param value the new transform
         */
        void set_transform(const glm::mat4& value);

        /*!
         * Get the node's transform.
         *
         * @return the node's current transform
         */
        const glm::mat4& get_transform() const;

        //! Move the node by a given amount.
        void move(const glm::vec3& value);

        //! Rotate the node by a given amount.
        void rotate(float angle, const glm::vec3& axis);

        //! Submit draw commands to the render queue.
        virtual void enqueue(RenderQueue& queue) const;

    private:
        Scene* scene = nullptr;
        glm::mat4 transform = glm::mat4(1.0f);

    friend class Scene;
    };
}

#endif
