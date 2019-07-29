// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_AMIENT_LIGHT_H_
#define _PKZO_AMIENT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    //! Ambient Light
    class PKZO_EXPORT AmbientLight : public Light
    {
    public:

        AmbientLight(const glm::vec3& color);

        void enqueue(RenderQueue& queue) const override;

    };
}

#endif
