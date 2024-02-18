// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <type_traits>

namespace rex
{
    template <typename Enum>
    constexpr auto to_underlying(Enum e)
    {
        return static_cast<std::underlying_type_t<Enum>>(e);
    }
}
