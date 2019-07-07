// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _HELLO_HELLO_ENGINE_H_
#define _HELLO_HELLO_ENGINE_H_

#include <pkzo/Engine.h>

#include "GreetingScreen.h"

namespace hello
{
    class HelloEngine : public pkzo::Engine
    {
    public:
        HelloEngine();
        
    private:
        GreetingScreen screen;
    };
}

#endif
