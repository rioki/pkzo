
#include "Geometry.h"

namespace pkzo
{
    Geometry::Geometry() {}

    Geometry::~Geometry() {}

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = value;
    }

    std::shared_ptr<Material> Geometry::get_material() const
    {
        return material;
    }
}
