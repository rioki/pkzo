//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "config.h"

#include <ratio>

namespace pkzo
{
    template <class _Ty>
    constexpr bool is_ratio_v = false;
    template <intmax_t R1, intmax_t R2>
    constexpr bool is_ratio_v<std::ratio<R1, R2>> = true;

    template <typename T = float, typename U = std::ratio<1>>
    class Mass
    {
    public:
        using rep = T;
        using unit = U;

        static_assert(std::is_arithmetic_v<T>, "type must be arithmetic");
        static_assert(is_ratio_v<U>, "unit not an instance of std::ratio");

        Mass() noexcept = default;

        constexpr Mass(T v) noexcept
        : value(v) {}

        template <typename T2>
        constexpr Mass(T2 v) noexcept
        : value(static_cast<T>(v)) {}

        Mass(const Mass<T, U>&) noexcept = default;
        Mass(Mass<T, U>&&) noexcept = default;

        ~Mass() = default;

        Mass<T, U>& operator = (const Mass<T, U>&) noexcept = default;
        Mass<T, U>& operator = (Mass<T, U>&&) noexcept = default;

        constexpr T count() const
        {
            return value;
        }

    private:
        T value = T(0);
    };

    template <class TO, class T, class U>
    constexpr TO mass_cast(const Mass<T, U>& m) noexcept
    {
        using div = std::ratio_divide<U, typename TO::unit>;
        using ComonType = std::common_type_t<typename TO::rep, T, intmax_t>;

        if (div::den == 1)
        {
            if (div::num == 1)
            {
                return TO(m.count());
            }
            else
            {
                return TO(static_cast<ComonType>(m.count()) * static_cast<ComonType>(div::num));
            }
        } else
        {
            if (div::num == 1)
            {
                return TO(static_cast<ComonType>(m.count()) / static_cast<ComonType>(div::den));
            }
            else
            {
                return TO(static_cast<ComonType>(m.count()) * static_cast<ComonType>(div::num) / static_cast<ComonType>(div::den));
            }
        }
    }

    using MilliGramm = Mass<double, std::milli>;
    using Gramm      = Mass<double>;
    using KiloGramm  = Mass<double, std::kilo>;
    using Tonne      = Mass<double, std::mega>;

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator == (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        // not sure if that is the best, but that is what is simple to implement
        auto b2 = mass_cast<Mass<T1, U1>>(b);
        return std::abs(a.count() - b2.count()) < T1(1.e-4f);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator != (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        return !(a == b);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator < (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        auto b2 = mass_cast<Mass<T1, U1>>(b);
        return a.count() < b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator > (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        auto b2 = mass_cast<Mass<T1, U1>>(b);
        return a.count() > b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator <= (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        return a == b || a < b;
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator >= (const Mass<T1, U1>& a, const Mass<T2, U2>& b) noexcept
    {
        return a == b || a > b;
    }

    namespace mass_literals
    {
        #pragma warning(push)
        #pragma warning(disable: 4244 4455)
        // Suppress warning about needing underscores...

        constexpr MilliGramm operator "" mg(long double value)
        {
            return MilliGramm(value);
        }

        constexpr Gramm operator "" g(long double value)
        {
            return Gramm(value);
        }

        constexpr KiloGramm operator "" kg(long double value)
        {
            return KiloGramm(value);
        }

        constexpr Tonne operator "" t(long double value)
        {
            return Tonne(value);
        }

        constexpr MilliGramm operator "" mg(unsigned long long int value)
        {
            return MilliGramm(value);
        }

        constexpr Gramm operator "" g(unsigned long long int value)
        {
            return Gramm(value);
        }

        constexpr KiloGramm operator "" kg(unsigned long long int value)
        {
            return KiloGramm(value);
        }

        constexpr Tonne operator "" t(unsigned long long int value)
        {
            return Tonne(value);
        }

        #pragma warning(pop)
    }
}
