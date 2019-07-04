// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SDL_SENTRY_H_
#define _PKZO_SDL_SENTRY_H_

#include <atomic>

namespace pkzo
{
    class SDLSentry
    {
    public:
        
        SDLSentry();

        SDLSentry(const SDLSentry&) = delete;

        ~SDLSentry();

        const SDLSentry& operator = (const SDLSentry&) = delete;  

    private:
        static std::atomic<size_t> use_count;
    };
}

#endif
