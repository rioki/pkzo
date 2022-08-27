// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <atomic>

namespace ice
{
    class ICE_EXPORT SdlSentry
    {
    public:
        SdlSentry();
        ~SdlSentry();

    private:
        static unsigned int init_count;

        SdlSentry(const SdlSentry& other) = delete;
        SdlSentry& operator = (const SdlSentry& other) = delete;
    };
}
