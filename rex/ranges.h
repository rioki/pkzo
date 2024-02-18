// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <functional>

namespace rex
{
    namespace ranges
    {
        template <typename C>
        struct to_helper {};

        template <typename C, std::ranges::range R>
        requires std::convertible_to<std::ranges::range_value_t<R>, typename C::value_type>
        C operator | (R&& r, to_helper<C>)
        {
            return {r.begin(), r.end()};
        }

        template <std::ranges::range C>
        requires (!std::ranges::view<C>)
        auto to()
        {
            return to_helper<C>{};
        }
    }
}