
#ifndef _PKZO_POINT_LIGHT_H_
#define _PKZO_POINT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    class PKZO_EXPORT PointLight : public Light
    {
    public:
        
        PointLight();

        ~PointLight();

        void set_range(float value);

        float get_range() const;

        void enqueue(SceneRenderer& renderer) const override;

    private:
        float range;
    };
}

#endif
