// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SYSTEM_H_
#define _PKZO_SYSTEM_H_

#include "defines.h"
#include "stdex.h"

namespace pkzo
{
    //! System Interface
    class PKZO_EXPORT System : public stdex::non_copyable
    {
    public:
        virtual ~System() = default;

        //! update system
        virtual void tick(float dt) = 0;
    };
}

#endif
