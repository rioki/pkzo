
#ifndef _PKZOSG_SCENE_H_
#define _PKZOSG_SCENE_H_

#include "defines.h"

namespace pkzo
{
    class PKZOSG_EXPORT Scene
    {
    public:
        
        Scene();

        Scene(const Scene&) = delete;

        ~Scene();

        const Scene& operator = (const Scene&) = delete;

    private:

    };
}

#endif
