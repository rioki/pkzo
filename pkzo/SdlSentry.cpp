// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "SDLSentry.h"

#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace pkzo
{
    std::atomic<size_t> SDLSentry::use_count(0);

    SDLSentry::SDLSentry()
    {
        size_t c = use_count.fetch_add(1);
        if (c == 0)
        {
            int r = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
            if (r < 0)
            {
                throw std::runtime_error(SDL_GetError());
            }

            r = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
            if (r < 0)
            {
                throw std::runtime_error(IMG_GetError());
            }

            r = TTF_Init();
            if (r < 0)
            {
                throw std::runtime_error(TTF_GetError());
            }
        }
    }

    SDLSentry::~SDLSentry()
    {
        size_t c = use_count.fetch_sub(1);
        if (c == 1)
        {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
        }
    }
}