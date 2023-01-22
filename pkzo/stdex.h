// stdext - small bits of code that should be standard, but aren't
// Copyright 2022-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <type_traits>

namespace stdex
{
    //! Helper to automatically decide optimal value passing type.
    //!
    //! This helper will decie if passing by value or const ref is the best
    //! option. This allows to always be right, even then code and types
    //! chang.
    template<typename T>
    using cref_t = std::conditional_t<sizeof(T) <
        2*sizeof(void*) && std::is_trivially_copy_constructible_v<T>,
        const T,
        const T&
    >;

    //! Argument specifier for input values.
    template<typename T>
    using in = cref_t<T>;
    //! Argument specifier for output values.
    template<typename T>
    using out = T&;
    //! Argument specifier for in/out values.
    template<typename T>
    using inout = T&;
    //! Argument specifier for input references.
    template<typename T>
    using inref = inout<T>;
    //! Argument specifier for move values.
    template<typename T>
    using move = T&&;

    //! Allow visiting of a variant with hetrogenious labda functions.
    //!
    //! @example
    //! @code
    //! std::variant<bool, int, float> my_variant;
    //!
    //! std::visit(stdext::overloaded {
    //!   [&] (bool v) { /* process bool value */ },
    //!   [&] (int v) { /* process int value */ },
    //!   [&] (float v) { /* process float value */ },
    //! }, my_variant);
    //! @endcode
    //! @{
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    //! @}
}
