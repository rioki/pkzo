
#include "TTFSentry.h"

#include <stdexcept>
#include <SDL_ttf.h>

namespace pkzo
{
    std::atomic<size_t> TTFSentry::use_count(0);

    TTFSentry::TTFSentry()
    {
        size_t c = use_count.fetch_add(1);
        if (c == 0)
        {
            int r = TTF_Init();
            if (r < 0)
            {
                throw std::runtime_error(TTF_GetError());
            }
        }
    }

    TTFSentry::~TTFSentry()
    {
        size_t c = use_count.fetch_sub(1);
        if (c == 1)
        {
            TTF_Quit();
        }
    }
}