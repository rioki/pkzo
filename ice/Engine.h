// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

namespace ice
{
    class ICE_EXPORT Engine
    {
    public:
        Engine();

        ~Engine();

    private:

        Engine(const Engine&) = delete;
        Engine& operator = (const Engine&) = delete;
    };
}
