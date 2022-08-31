// glm 2d helpers
// Copyright 2022 Sean Farrell <sean.farrell@rioki.org>
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

    // This is not 2d, but it is "missing" in glm...
    // (There is the quaternion version, but IMHO this should exist for mat4)
    template<typename T, qualifier Q>
    vec<3, T, Q> transform(const mat<4, 4, T, Q>& matrix, const vec<3, T, Q>& value) noexcept
    {
        return vec<3, T, Q>(matrix * vec<4, T, Q>(value, 1.0f));
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> translate(const vec<2, T, Q>& pos) noexcept
    {
        auto result = mat<3, 3, T, Q>(1.0f);

        result[2][0] = pos[0];
        result[2][1] = pos[1];

        return result;
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> translate(const mat<3, 3, T, Q>& matrix, const vec<2, T, Q>& value) noexcept
    {
        return matrix * translate<T, Q>(value);
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> rotate(const T angle) noexcept
    {
        auto result = mat<3, 3, T, Q>(1.0f);

        auto cosa = std::cos(angle);
        auto sina = std::sin(angle);

        result[0][0] = cosa;  result[1][0] = -sina;
        result[0][1] = sina;  result[1][1] =  cosa;

        return result;
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> rotate(const mat<3, 3, T, Q>& matrix, const T angle) noexcept
    {
        return matrix * rotate<T, Q>(angle);
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> scale(const vec<2, T, Q>& pos) noexcept
    {
        auto result = mat<3, 3, T, Q>(1.0f);

        result[0][0] = pos[0];
        result[1][1] = pos[1];

        return result;
    }

    template<typename T, qualifier Q>
    mat<3, 3, T, Q> scale(const mat<3, 3, T, Q>& matrix, const vec<2, T, Q>& value) noexcept
    {
        return matrix * scale<T, Q>(value);
    }

    template<typename T, qualifier Q>
    mat<4, 4, T, Q> to3d(const mat<3, 3, T, Q>& t) noexcept
    {
        auto r = mat<4, 4, T, Q>(1.0f);

        r[0][0] = t[0][0]; r[1][0] = t[1][0]; r[3][0] = t[2][0];
        r[0][1] = t[0][1]; r[1][1] = t[1][1]; r[3][1] = t[2][1];

        return r;
    }
}
