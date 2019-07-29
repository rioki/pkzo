// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_POINT_LIGHT_H_
#define _PKZO_POINT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    //! Poitn Light
    class PKZO_EXPORT PointLight : public Light
    {
    public:

        void enqueue(RenderQueue& queue) const override;

    };
}

#endif
