// strconv
// Copyright 2022-2025 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include "strconv.h"

#include <stdexcept>
#include <vector>
#include <iconv.h>

#include "stdng.h"

namespace strconv
{
    template <typename CharT>
    struct CharTraits {};

    template <>
    struct CharTraits<char>
    {
        // Empty string is whatever the system uses as multibyte encoding
        static constexpr const char* encoding = "";
    };

    template <>
    struct CharTraits<wchar_t>
    {
    #if defined(_WIN32)
        static constexpr const char* encoding = "UTF-16LE";
    #elif __APPLE__
        // macOS iconv doesn't always support UTF-32LE, so check locale too if needed
        static constexpr const char* encoding = "UTF-32LE";
    #elif defined(__linux__)
        static constexpr const char* encoding = (sizeof(wchar_t) == 2)
            ? "UTF-16LE"
            : "UTF-32LE";
    #else
        #error "Unknown platform: cannot determine wchar_t encoding"
    #endif

        static_assert(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4, "Unsupported wchar_t size");
    };

    template <>
    struct CharTraits<char8_t>
    {
        static constexpr const char* encoding = "UTF-8";
    };

    template <>
    struct CharTraits<char16_t>
    {
        static constexpr const char* encoding = "UTF-16LE";
    };

    template <>
    struct CharTraits<char32_t>
    {
        static constexpr const char* encoding = "UTF-32LE";
    };

    template <typename ToCharT, typename FromCharT>
    std::basic_string<ToCharT> iconv_impl(const std::basic_string_view<FromCharT> input)
    {
        auto result = std::basic_string<ToCharT>{};
        result.reserve(input.size());

        const auto from = CharTraits<FromCharT>::encoding;
        const auto to   = CharTraits<ToCharT>::encoding;

        auto cd = iconv_open(to, from);
        if (cd == reinterpret_cast<iconv_t>(-1))
        {
            throw std::runtime_error("iconv_open failed");
        }

        auto cleanup = stdng::scope_exit([cd]() {
            iconv_close(cd);
        });

        auto inbuf       = reinterpret_cast<char*>(const_cast<FromCharT*>(input.data()));
        auto inbytesleft = input.size() * sizeof(FromCharT);

        auto temp         = std::vector<char>(1024);
        while (inbytesleft > 0u)
        {
            auto outbuf       = temp.data();
            auto outbytesleft = temp.size();

            errno = 0;
            auto res = iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
            if (res == static_cast<size_t>(-1))
            {
                switch (errno)
                {
                    case E2BIG:
                        // Output buffer full, not fatal: handled in loop
                        break;
                    case EILSEQ:
                        throw std::runtime_error("Invalid multibyte sequence");
                    case EINVAL:
                        throw std::runtime_error("Incomplete multibyte sequence");
                    default:
                        throw std::runtime_error("Unknown iconv error");
                }
            }

            size_t bytes_produced = temp.size() - outbytesleft;
            if (bytes_produced % sizeof(ToCharT) != 0)
            {
                throw std::runtime_error("Misaligned iconv output");
            }

            auto count = bytes_produced / sizeof(ToCharT);
            result.insert(result.end(),
                          reinterpret_cast<const ToCharT*>(temp.data()),
                          reinterpret_cast<const ToCharT*>(temp.data()) + count);
        }

        return result;
    }

    std::string narrow(const std::string_view input)
    {
        return std::string(input);
    }

    std::string narrow(const std::wstring_view input)
    {
        return iconv_impl<char>(input);
    }

    std::string narrow(const std::u8string_view input)
    {
        return iconv_impl<char>(input);
    }

    std::string narrow(const std::u16string_view input)
    {
        return iconv_impl<char>(input);
    }

    std::string narrow(const std::u32string_view input)
    {
        return iconv_impl<char>(input);
    }

    std::wstring widen(const std::string_view input)
    {
        return iconv_impl<wchar_t>(input);
    }

    std::wstring widen(const std::wstring_view input)
    {
        return std::wstring(input);
    }

    std::wstring widen(const std::u8string_view input)
    {
        return iconv_impl<wchar_t>(input);
    }

    std::wstring widen(const std::u16string_view input)
    {
        return iconv_impl<wchar_t>(input);
    }

    std::wstring widen(const std::u32string_view input)
    {
        return iconv_impl<wchar_t>(input);
    }

    std::u8string utf8(const std::string_view input)
    {
        return iconv_impl<char8_t>(input);
    }
    std::u8string utf8(const std::wstring_view input)
    {
        return iconv_impl<char8_t>(input);
    }

    std::u8string utf8(const std::u8string_view input)
    {
        return std::u8string(input);
    }

    std::u8string utf8(const std::u16string_view input)
    {
        return iconv_impl<char8_t>(input);
    }

    std::u8string utf8(const std::u32string_view input)
    {
        return iconv_impl<char8_t>(input);
    }

    std::u16string utf16(const std::string_view input)
    {
        return iconv_impl<char16_t>(input);
    }

    std::u16string utf16(const std::wstring_view input)
    {
        return iconv_impl<char16_t>(input);
    }

    std::u16string utf16(const std::u8string_view input)
    {
        return iconv_impl<char16_t>(input);
    }

    std::u16string utf16(const std::u16string_view input)
    {
        return std::u16string(input);
    }

    std::u16string utf16(const std::u32string_view input)
    {
        return iconv_impl<char16_t>(input);
    }

    std::u32string utf32(const std::string_view input)
    {
        return iconv_impl<char32_t>(input);
    }

    std::u32string utf32(const std::wstring_view input)
    {
        return iconv_impl<char32_t>(input);
    }

    std::u32string utf32(const std::u8string_view input)
    {
        return iconv_impl<char32_t>(input);
    }

    std::u32string utf32(const std::u16string_view input)
    {
        return iconv_impl<char32_t>(input);
    }

    std::u32string utf32(const std::u32string_view input)
    {
        return std::u32string(input);
    }

    std::string u8compat(const std::u8string_view input)
    {
        return std::string(reinterpret_cast<const char*>(input.data()), input.size());
    }

    std::u8string u8compat(const std::string_view input)
    {
        return std::u8string(reinterpret_cast<const char8_t*>(input.data()), input.size());
    }
}
