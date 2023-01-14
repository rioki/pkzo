// glm helpers
// Copyright 2022-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <glm/glm.hpp>

namespace glm
{
    template<typename T, qualifier Q>
    vec<2, T, Q> transform(const mat<3, 3, T, Q>& matrix, const vec<2, T, Q>& value) noexcept
    {
        return vec<2, T, Q>(matrix * vec<3, T, Q>(value, 1.0f));
    }

    template<typename T, qualifier Q>
    vec<3, T, Q> transform(const mat<4, 4, T, Q>& matrix, const vec<3, T, Q>& value) noexcept
    {
        return vec<3, T, Q>(matrix * vec<4, T, Q>(value, 1.0f));
    }

    template<length_t L, typename T, qualifier Q>
    bool close(const glm::vec<L,T,Q>& a, const glm::vec<L,T,Q>& b, T eps)
    {
        return glm::all(glm::lessThan(glm::abs(a - b), glm::vec<L,T,Q>(eps)));
    }

    template<length_t M, length_t N, typename T, qualifier Q>
    bool close(const glm::mat<M, N,T,Q>& a, const glm::mat<M, N, T, Q>& b, T eps)
    {
        for (auto i = 0u; i < M; i++)
        {
            if (! close(a[i], b[i], eps))
            {
                return false;
            }
        }
        return true;
    }
}
