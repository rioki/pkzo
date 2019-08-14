// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SDL_SENTRY_H_
#define _PKZO_SDL_SENTRY_H_

#include "defines.h"

#include <atomic>
#include "stdex.h"

namespace pkzo
{
    class PKZO_EXPORT SdlSentry : public stdex::non_copyable
    {
    public:

        SdlSentry();

        ~SdlSentry();

    private:
        static std::atomic<size_t> count;
    };
}

#endif
