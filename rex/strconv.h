// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <locale>
#include <string_view>

#include "defines.h"

namespace rex
{
    //! Convert wide string to multibyte string
    //!
    //! The narrow function converts any wide or unicode string to the system's
    //! mutlibyte encoding.
    //!
    //! @{
    REX_EXPORT [[nodiscard]] std::string narrow(const std::string_view& input);
    REX_EXPORT [[nodiscard]] std::string narrow(const std::wstring_view& input);
    REX_EXPORT [[nodiscard]] std::string narrow(const std::u8string_view& input);
    REX_EXPORT [[nodiscard]] std::string narrow(const std::u16string_view& input);
    REX_EXPORT [[nodiscard]] std::string narrow(const std::u32string_view& input);
    //! @}

    //! Convert to wide string.
    //!
    //! @{
    REX_EXPORT [[nodiscard]] std::wstring widen(const std::string_view& input);
    REX_EXPORT [[nodiscard]] std::wstring widen(const std::wstring_view& input);
    REX_EXPORT [[nodiscard]] std::wstring widen(const std::u8string_view& input);
    REX_EXPORT [[nodiscard]] std::wstring widen(const std::u16string_view& input);
    REX_EXPORT [[nodiscard]] std::wstring widen(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-8 string
    //!
    //! @{
    REX_EXPORT [[nodiscard]] std::u8string utf8(const std::string_view& input);
    REX_EXPORT [[nodiscard]] std::u8string utf8(const std::wstring_view& input);
    REX_EXPORT [[nodiscard]] std::u8string utf8(const std::u8string_view& input);
    REX_EXPORT [[nodiscard]] std::u8string utf8(const std::u16string_view& input);
    REX_EXPORT [[nodiscard]] std::u8string utf8(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-16 string
    //!
    //! @{
    REX_EXPORT [[nodiscard]] std::u16string utf16(const std::string_view& input);
    REX_EXPORT [[nodiscard]] std::u16string utf16(const std::wstring_view& input);
    REX_EXPORT [[nodiscard]] std::u16string utf16(const std::u8string_view& input);
    REX_EXPORT [[nodiscard]] std::u16string utf16(const std::u16string_view& input);
    REX_EXPORT [[nodiscard]] std::u16string utf16(const std::u32string_view& input);
    //! @}

    //! Convert string to UTF-32 string
    //!
    //! @{
    REX_EXPORT [[nodiscard]] std::u32string utf32(const std::string_view& input);
    REX_EXPORT [[nodiscard]] std::u32string utf32(const std::wstring_view& input);
    REX_EXPORT [[nodiscard]] std::u32string utf32(const std::u8string_view& input);
    REX_EXPORT [[nodiscard]] std::u32string utf32(const std::u16string_view& input);
    REX_EXPORT [[nodiscard]] std::u32string utf32(const std::u32string_view& input);
    //! @}

    //! Blind cast a UTF-8 string into std::string
    REX_EXPORT [[nodiscard]] std::string u8compat(const std::u8string_view& input);
    //! Interprete a std::string as containing UTF-8 data.
    REX_EXPORT [[nodiscard]] std::u8string u8compat(const std::string_view& input);
}