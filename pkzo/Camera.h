// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_CAMERA_H_
#define _PKZO_CAMERA_H_

#include "SceneNode.h"

namespace pkzo
{
    /*!
     * Camera
     */
    class PKZO_EXPORT Camera : public SceneNode
    {
    public:
        Camera();
        ~Camera();

        /*!
         * The horizontal field of view.
         *
         * @{
         */
        void set_fov(float value);
        float get_fov() const;
        /*! @} */

        void set_resolution(glm::uvec2 value);
        glm::uvec2 get_resolution() const;

        glm::mat4 get_projection() const;
        glm::mat4 get_view() const;

    private:
        float fov = 90.0f;
        glm::uvec2 resolution = glm::uvec2(800, 600);
    };
}

#endif
