// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_LIGHT_H_
#define _PKZO_LIGHT_H_

#include "SceneNode.h"

namespace pkzo
{
    //! Light Base
    class PKZO_EXPORT Light : public SceneNode
    {
    public:
        Light(const glm::vec3& color = {1.0f, 1.0f, 1.0f});

        //! Set the light's color.
        void set_color(const glm::vec3& value);

        //! Get the lights color.
        const glm::vec3& get_color() const;

    protected:
        glm::vec3 color = {1.0f, 1.0f, 1.0f};
    };
}

#endif
