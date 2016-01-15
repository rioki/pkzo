
#ifndef _PKZO_AMBIENT_LIGHT_H_
#define _PKZO_AMBIENT_LIGHT_H_

#include "Light.h"

namespace pkzo
{
    class PKZO_EXPORT AmbientLight : public Light
    {
    public:
        AmbientLight();

        ~AmbientLight();

        void enqueue(SceneRenderer& renderer) const override;

    private:
        
    };
}

#endif
