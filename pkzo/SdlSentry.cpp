
// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "SdlSentry.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace pkzo
{
    std::atomic<size_t> SdlSentry::count = 0;

    SdlSentry::SdlSentry()
    {
        if (count++ == 0)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            {
                throw std::runtime_error(SDL_GetError());
            }
            if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) < 0)
            {
                throw std::runtime_error(IMG_GetError());
            }
            if (TTF_Init() < 0)
            {
                throw std::runtime_error(TTF_GetError());
            }
        }
    }

    SdlSentry::~SdlSentry()
    {
        if (--count == 0)
        {
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
        }
    }
}

