
#ifndef _PKZO_SPOT_LIGHT_H_
#define _PKZO_SPOT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    class PKZO_EXPORT SpotLight : public pkzo::Light
    {
    public:
        
        SpotLight();

        ~SpotLight();

        void set_range(float value);

        float get_range() const;

        void set_angle(float value);

        float get_angle() const;

        void enqueue(SceneRenderer& renderer) const override;

    private:
        float range;
        float angle;
    };
}

#endif