
#include "PointLight.h"

#include "SceneRenderer.h"

namespace pkzo
{
    PointLight::PointLight()
    : range(10) {}

    PointLight::~PointLight() {}

    void PointLight::set_range(float value)
    {
        range = value;
    }

    float PointLight::get_range() const
    {
        return range;
    }

    void PointLight::enqueue(SceneRenderer& renderer) const
    {
        renderer.queue_point_light(get_world_position(), get_color(), range);
    }
}