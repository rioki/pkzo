// C++ Standard Next Generation
// Stuff that will be in the C++ standard, but available today.
// Copyright 2025 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <string.h>
#include <memory>
#include <type_traits>
#include <utility>
#include <tuple>
#include <array>
#include <iostream>

namespace stdng
{
    template <class EF>
    class scope_exit
    {
    public:
        scope_exit(EF&& fn) noexcept
        : exitfun(fn) {}

        scope_exit(scope_exit&& other) noexcept
        : exitfun(std::move(other.exitfun)), active(other.active)
        {
            other.release();
        }

        ~scope_exit()
        {
            if (active)
            {
                exitfun();
            }
        }

        void release() noexcept
        {
            active = false;
        }

    private:
        EF exitfun;
        bool active = true;

        scope_exit(const scope_exit&) = delete;
        scope_exit& operator = (const scope_exit&) = delete;
    };

    template <class EF>
    class scope_fail
    {
    public:

        explicit scope_fail(EF&& fn) noexcept
        : exitfun(std::move(fn)), exception_count(std::uncaught_exceptions()) {}

        scope_fail(scope_fail&& other) noexcept
        : exitfun(std::move(other.exitfun)), active(other.active), exception_count(other.exception_count)
        {
            other.release();
        }

        ~scope_fail()
        {
            if (active && std::uncaught_exceptions() > exception_count)
            {
                exitfun();
            }
        }

        void release() noexcept
        {
            active = false;
        }

    private:
        EF   exitfun;
        bool active = true;
        int  exception_count;

        scope_fail(const scope_fail&)            = delete;
        scope_fail& operator=(const scope_fail&) = delete;
    };

    template <class EF>
    class scope_success
    {
    public:

        explicit scope_success(EF&& fn) noexcept
        : exitfun(std::move(fn)), exception_count(std::uncaught_exceptions()) {}

        scope_success(scope_success&& other) noexcept
        : exitfun(std::move(other.exitfun)), active(other.active), exception_count(other.exception_count)
        {
            other.release();
        }

        ~scope_success()
        {
            if (active && std::uncaught_exceptions() <= exception_count)
            {
                exitfun();
            }
        }

        void release() noexcept
        {
            active = false;
        }

    private:
        EF   exitfun;
        bool active = true;
        int  exception_count;

        scope_success(const scope_success&)            = delete;
        scope_success& operator=(const scope_success&) = delete;
    };


    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        auto h = std::hash<T>{}(v);
        seed ^= h + 0x9e3779b97f4a7c15ull + (seed << 6) + (seed >> 2);
    }

    constexpr unsigned int hash_impl(const char* str, size_t len, int i = 0)
    {
        return i == len ? 5381u : (hash_impl(str, len, i+1)*33) ^ str[i];
    }

    constexpr unsigned int hash(const std::string_view str)
    {
        return hash_impl(str.data(), str.size());
    }
}

namespace std
{
    template <class... Ts>
    struct hash<tuple<Ts...>>
    {
        std::size_t operator()(std::tuple<Ts...> const& t) const noexcept
        {
            std::size_t seed = 0;
            std::apply([&](auto const&... xs) {
                (stdng::hash_combine(seed, xs), ...);
            }, t);
            return seed;
        }
    };
}

#ifndef _STD_ARRAY_STREAM_
#define _STD_ARRAY_STREAM_
namespace std
{
    // Pretend array<char, N> is like const char[N] when it comes to streaming.
    template <size_t N>
    ostream& operator << (ostream& os, const array<char, N>& buff)
    {
        auto len = strnlen(buff.data(), N);
        os.write(buff.data(), len);
        return os;
    }
}
#endif
