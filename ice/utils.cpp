// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "utils.h"

namespace ice
{
    void trace(const std::string_view msg)
    {
        OutputDebugStringA(msg.data());
    }
}
