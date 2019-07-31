// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_GEOMETRY_H_
#define _PKZO_GEOMETRY_H_

#include "SceneNode.h"

namespace pkzo
{
    class Material;

    //! Geometry base class.
    class PKZO_EXPORT Geometry : public SceneNode
    {
    public:
        Geometry(std::shared_ptr<Material> material);
        ~Geometry();

        //! Change the material.
        void set_material(std::shared_ptr<Material> value);

        //! Get the material.
        std::shared_ptr<Material> get_material();

    protected:
        std::shared_ptr<Material> material;
    };
}

#endif
