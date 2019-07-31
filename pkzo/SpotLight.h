// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SPOT_LIGHT_H_
#define _PKZO_SPOT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    //! Spot Light
    class PKZO_EXPORT SpotLight : public Light
    {
    public:
        //! Create spot light with given color and angle.
        SpotLight(const glm::vec3& color, float a);

        //! Set the spot angle.
        void set_angle(float value);

        //! Get the spot angle.
        float get_angle() const;

        void enqueue(RenderQueue& queue) const override;

    private:
        float angle = 25.0f;
    };
}

#endif
