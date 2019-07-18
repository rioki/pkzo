// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_COLOR_MODE_H_
#define _PKZO_COLOR_MODE_H_

#include "defines.h"

namespace pkzo
{
    enum class ColorMode
    {
        GRAYSCALE,
        RGB,
        RGBA,
        DEPTH,
        GRAYSCALE_FLOAT,
        RGB_FLOAT,
        RGBA_FLOAT,
        DEPTH_FLOAT
    };
}

#endif
