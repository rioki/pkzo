
#include "Light.h"

namespace pkzo
{
    Light::Light()
    : color(1.0f) {}

    Light::~Light() {}

    void Light::set_color(const Color& value)
    {
        color = value;
    }

    const Color& Light::get_color() const
    {
        return color;
    }
}
