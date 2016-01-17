
#include "SpotLight.h"

#include "SceneRenderer.h"

namespace pkzo
{
    SpotLight::SpotLight() 
    : range(10), angle(25) {}

    SpotLight::~SpotLight() {}

    void SpotLight::set_range(float value)
    {
        range = value;
    }

    float SpotLight::get_range() const
    {
        return range;
    }

    void SpotLight::set_angle(float value)
    {
        angle = value;
    }

    float SpotLight::get_angle() const
    {
        return angle;
    }

    void SpotLight::enqueue(SceneRenderer& renderer) const
    {
        Quaternion o   = get_world_orientation();
        Vector3    dir = transform(o, Vector3(0, 0, 1));

        renderer.queue_spot_light(get_world_position(), dir, get_color(), range, angle);
    }
}
