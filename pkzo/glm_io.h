// glm stream operators
// Copyright 2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace glm
{
    template<size_t N, typename T, qualifier Q>
    std::ostream& operator << (std::ostream& os, const vec<N, T, Q>& v)
    {
        os << "(";
        for (auto i = 0u; i < N; i++)
        {
            os << v[i];
            if (i != N - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    template<size_t N, size_t M, typename T, qualifier Q>
    std::ostream& operator << (std::ostream& os, const mat<N, M, T, Q>& v)
    {
        os << "(";
        for (auto i = 0u; i < N; i++)
        {
            os << v[i];
            if (i != N - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    template<size_t N, typename T, qualifier Q>
    std::istream& operator >> (std::istream& is, vec<N, T, Q>& v)
    {
        char c;
        is >> c;
        assert(c == '(');
        for (auto i = 0u; i < N; i++)
        {
            is >> v[i];
            if (i != N - 1)
            {
                is >> c;
                assert(c == ',');
            }
        }
        is >> c;
        assert(c == ')');
        return is;
    }

    template<size_t N, size_t M, typename T, qualifier Q>
    std::istream& operator >> (std::istream& is, mat<N, M, T, Q>& v)
    {
        char c;
        is >> c;
        assert(c == '(');
        for (auto i = 0u; i < N; i++)
        {
            is >> v[i];
            if (i != N - 1)
            {
                is >> c;
                assert(c == ',');
            }
        }
        is >> c;
        assert(c == ')');
        return is;
    }
}
