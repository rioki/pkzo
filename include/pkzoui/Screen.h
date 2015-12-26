
#ifndef _PKZOUI_SCREEN_H_
#define _PKZOUI_SCREEN_H_

#include "defines.h"

namespace pkzoui
{
    class PKZOUI_EXPORT Screen
    {
    public:
        Screen();

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;
    };
}

#endif
