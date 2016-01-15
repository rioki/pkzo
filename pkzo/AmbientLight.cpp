
#include "AmbientLight.h"

#include "SceneRenderer.h"

namespace pkzo
{
    AmbientLight::AmbientLight()
    {
    }

    AmbientLight::~AmbientLight()
    {
    }

    void AmbientLight::enqueue(SceneRenderer& renderer) const
    {
        renderer.queue_ambient_light(color);
    }
}