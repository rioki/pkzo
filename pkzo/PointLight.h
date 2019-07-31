// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_POINT_LIGHT_H_
#define _PKZO_POINT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    //! Point Light
    class PKZO_EXPORT PointLight : public Light
    {
    public:
        //! Construct a point light with given color.
        PointLight(const glm::vec3& color);

        void enqueue(RenderQueue& queue) const override;

    };
}

#endif
