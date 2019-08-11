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
        //! Set the horizontal field of view.
        void set_fov(float value);

        //! Get the horizontal field of view.
        float get_fov() const;

        glm::mat4 get_projection_matrix(float aspect, float distance) const;

        glm::mat4 get_view_matrix() const;

        //! Set the camera on the render queue up.
        void setup(RenderQueue& queue) const;

    private:
        float fov = 90.0f;
    };
}

#endif
