
#ifndef _PKZOSG_DIRECTIONAL_LIGHT_H_
#define _PKZOSG_DIRECTIONAL_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    class PKZOSG_EXPORT DirectionalLight : public Light
    {
    public:
        
        DirectionalLight();

        ~DirectionalLight();        
        
        void enqueue(SceneRenderer & renderer) const override;
    };
}

#endif
