// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "SdlSentry.h"

namespace ice
{
    unsigned int SdlSentry::init_count = 0;

    SdlSentry::SdlSentry()
    {
        if (init_count++ == 0)
        {
            auto r = SDL_Init(SDL_INIT_EVERYTHING);
            if (r < 0)
            {
                throw std::runtime_error(SDL_GetError());
            }
        }
    }

    SdlSentry::~SdlSentry()
    {
        if (--init_count == 0)
        {
            SDL_Quit();
        }
    }
}
