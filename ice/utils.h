// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <string>
#include <string_view>
#include <sstream>

namespace ice
{
    template <typename T>
    std::string to_string(const T& value)
    {
        auto buff = std::stringstream{};
        buff << value;
        return buff.str();
    }

    template <typename T>
    T from_string(const std::string_view value)
    {
        auto buff = std::stringstream{value};
        auto value = T{};
        buff >> value;
        return value;
    }
}
