// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_DIRECTIONAL_LIGHT_H_
#define _PKZO_DIRECTIONAL_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    //! Directional Light
    class PKZO_EXPORT DirectionalLight : public Light
    {
    public:

        void enqueue(RenderQueue& queue) const override;

    };
}

#endif
