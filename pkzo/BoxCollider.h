// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_BOX_COLLIDER_H_
#define _PKZO_BOX_COLLIDER_H_

#include "Collider.h"

class btBoxShape;

namespace pkzo
{
    //! Box Collider
    class PKZO_EXPORT BoxCollider : public Collider
    {
    public:
        //! Create box collider.
        BoxCollider(const glm::vec3& size = {1.0f, 1.0f, 1.0f});
        //! Get the size of the box.
        const glm::vec3& get_size() const;

    protected:
        std::shared_ptr<btCollisionShape> get_collision_shape() override;

    private:
        glm::vec3                   size;
        std::shared_ptr<btBoxShape> collision_shape;
    };
}

#endif
