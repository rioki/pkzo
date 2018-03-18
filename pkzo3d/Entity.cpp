#include "Entity.h"

namespace pkzo
{

    Entity::Entity()
    : parent(nullptr), position(0), orientation(0, 0, 0, 1) {}


    Entity::~Entity() {}

    void Entity::set_position(const rgm::vec3& value)
    {
        position = value;
    }

    const rgm::vec3& Entity::get_position() const
    {
        return position;
    }

    rgm::vec3 Entity::get_world_position() const
    {
        if (parent != nullptr)
        {                      
           rgm::quat pwq = parent->get_world_orientation();
            return parent->get_world_position() + rgm::transform(pwq, position);
        }
        else
        {
            return position;
        }
    }

    void Entity::set_orientation(const rgm::quat& value)
    {
        orientation = value;
    }

    const rgm::quat& Entity::get_orientation() const
    {
        return orientation;
    }

   rgm::quat Entity::get_world_orientation() const
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

   rgm::mat4 Entity::get_transform() const
    {
       rgm::vec3 s = get_position();
       rgm::quat o = get_orientation();

       rgm::mat4 t(1);
        t = translate(t, s);
        t = rotate(t, o);

        return t;
    }

   rgm::mat4 Entity::get_world_transform() const
    {
       rgm::vec3 s = get_world_position();
       rgm::quat o = get_world_orientation();

       rgm::mat4 t(1);
        t = rgm::translate(t, s);
        t = rgm::rotate(t, o);

        return t;
    }
}