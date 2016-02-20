#include "Entity.h"

namespace pkzo
{

    Entity::Entity()
    : parent(nullptr), position(0), orientation(0, 0, 0, 1) {}


    Entity::~Entity() {}

    void Entity::set_position(const vec3& value)
    {
        position = value;
    }

    const vec3& Entity::get_position() const
    {
        return position;
    }

    vec3 Entity::get_world_position() const
    {
        if (parent != nullptr)
        {                      
            quat pwq = parent->get_world_orientation();
            return parent->get_world_position() + transform(pwq, position);
        }
        else
        {
            return position;
        }
    }

    void Entity::set_orientation(const quat& value)
    {
        orientation = value;
    }

    const quat& Entity::get_orientation() const
    {
        return orientation;
    }

    quat Entity::get_world_orientation() const
    {
        if (parent != nullptr)
        {
            return parent->get_world_orientation() * orientation;
        }
        else
        {
            return orientation;
        }
    }
}