// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_BODY_H_
#define _PKZO_BODY_H_

#include "SceneNodeGroup.h"

namespace pkzo
{
    //! Physical body
    class PKZO_EXPORT Body : public SceneNodeGroup
    {
    public:
        //! Construct body.
        Body(float mass);

        //! Set the bodies mass.
        void set_mass(float value);

        //! Get the bodies mass.
        float get_mass() const;

        void activate() override;
        void deactivate() override;

    private:
        float mass;
    };
}

#endif
