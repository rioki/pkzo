// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <memory>

namespace rex
{
    template <typename To, typename From, typename Deleter>
    std::unique_ptr<To, Deleter> dynamic_unique_cast(std::unique_ptr<From, Deleter>&& ptr)
    {
        auto to = dynamic_cast<To*>(ptr.get());
        if (to == nullptr)
        {
            return std::unique_ptr<To, Deleter>(nullptr);
        }

        // Only releasse when the cast was successfull.
        auto result = std::unique_ptr<To, Deleter>(to, ptr.get_deleter());
        ptr.release();
        return result;
    }
}