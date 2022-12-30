// strex - string utilities that should be standard
// Copyright 2022 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <locale>
#include <string_view>

#ifdef STREX_DLL
#define STREX_EXPORT __declspec(dllexport)
#else
#define STREX_EXPORT
#endif

namespace strex
{
    //! Convert wide string to multibyte string
    //!
    //! The narrow function converts any wide or unicode string to the system's
    //! mutlibyte encoding.
    //!
    //! @{
    STREX_EXPORT [[nodiscard]] std::string narrow(const std::string_view& input);
    STREX_EXPORT [[nodiscard]] std::string narrow(const std::wstring_view& input);
    STREX_EXPORT [[nodiscard]] std::string narrow(const std::u8string_view& input);
    STREX_EXPORT [[nodiscard]] std::string narrow(const std::u16string_view& input);
    STREX_EXPORT [[nodiscard]] std::string narrow(const std::u32string_view& input);
    //! @}

    //! Convert to wide string.
    //!
    //! @{
    STREX_EXPORT [[nodiscard]] std::wstring widen(const std::string_view& input);
    STREX_EXPORT [[nodiscard]] std::wstring widen(const std::wstring_view& input);
    STREX_EXPORT [[nodiscard]] std::wstring widen(const std::u8string_view& input);
    STREX_EXPORT [[nodiscard]] std::wstring widen(const std::u16string_view& input);
    STREX_EXPORT [[nodiscard]] std::wstring widen(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-8 string
    //!
    //! @{
    STREX_EXPORT [[nodiscard]] std::u8string utf8(const std::string_view& input);
    STREX_EXPORT [[nodiscard]] std::u8string utf8(const std::wstring_view& input);
    STREX_EXPORT [[nodiscard]] std::u8string utf8(const std::u8string_view& input);
    STREX_EXPORT [[nodiscard]] std::u8string utf8(const std::u16string_view& input);
    STREX_EXPORT [[nodiscard]] std::u8string utf8(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-8 string
    //!
    //! @{
    STREX_EXPORT [[nodiscard]] std::u16string utf16(const std::string_view& input);
    STREX_EXPORT [[nodiscard]] std::u16string utf16(const std::wstring_view& input);
    STREX_EXPORT [[nodiscard]] std::u16string utf16(const std::u8string_view& input);
    STREX_EXPORT [[nodiscard]] std::u16string utf16(const std::u16string_view& input);
    STREX_EXPORT [[nodiscard]] std::u16string utf16(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-8 string
    //!
    //! @{
    STREX_EXPORT [[nodiscard]] std::u32string utf32(const std::string_view& input);
    STREX_EXPORT [[nodiscard]] std::u32string utf32(const std::wstring_view& input);
    STREX_EXPORT [[nodiscard]] std::u32string utf32(const std::u8string_view& input);
    STREX_EXPORT [[nodiscard]] std::u32string utf32(const std::u16string_view& input);
    STREX_EXPORT [[nodiscard]] std::u32string utf32(const std::u32string_view& input);
    //! @}
}
