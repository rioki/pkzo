
#include "DirectionalLight.h"

#include "SceneRenderer.h"

namespace pkzo
{
    DirectionalLight::DirectionalLight() {}

    DirectionalLight::~DirectionalLight() {}

    void DirectionalLight::enqueue(SceneRenderer & renderer) const
    {
        Quaternion o   = get_world_orientation();
        Vector3    dir = transform(o, Vector3(0, 0, 1));

        renderer.queue_directional_light(dir, get_color());
    }
}
