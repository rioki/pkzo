// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _HELLO_GREETING_SCREEN_H_
#define _HELLO_GREETING_SCREEN_H_

#include <pkzo/Screen.h>

namespace hello
{
    class GreetingScreen : public pkzo::Screen
    {
    public:
        GreetingScreen(const glm::vec2& size);
    };
}

#endif
