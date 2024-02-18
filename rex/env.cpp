// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include "env.h"

namespace rex
{
    std::string file_name(const std::string_view& path) noexcept
    {
        auto pos = path.find_last_of("/\\");
        if (pos == std::string_view::npos)
        {
            return std::string{path};
        }
        else
        {
            return std::string{path.substr(pos + 1)};
        }
    }

    std::string get_env_variable(const std::string_view name) noexcept
    {
        auto buffer = std::array<char, MAX_PATH>{};
        auto len    = size_t{0};

        const auto err = getenv_s(&len, buffer.data(), buffer.size(), name.data());
        if (err == 0) // was found
        {
            return std::string(buffer.data(), len);
        }

        return {};
    }

    std::filesystem::path get_temp_folder()
    {
        #ifdef _WIN32
        std::array<wchar_t, MAX_PATH> buff;
        const auto hr = GetTempPathW(static_cast<DWORD>(buff.size()), buff.data());
        if (hr < 0)
        {
            throw std::logic_error("Could not determain TEMP folder.");
        }
        return buff.data();
        #endif

        return get_env_variable("TEMP");
    }

    std::filesystem::path get_user_folder()
    {
        #ifdef _WIN32
        std::array<wchar_t, MAX_PATH> buff;
        const auto hr = SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, buff.data());
        if (hr < 0)
        {
            throw std::logic_error("Could not determain APPDATA folder.");
        }
        return buff.data();
        #else
        return get_env_variable("TEMP");
        #endif
    }

    std::string get_module_filename() noexcept
    {
        #ifdef _WIN32
        auto handle = GetModuleHandleA(NULL);
        if (handle == NULL)
        {
            return "";
        }

        auto buff = std::array<char, MAX_PATH>{};
        auto r = GetModuleFileNameA(handle, buff.data(), static_cast<DWORD>(buff.size()));
        if (r == 0)
        {
            return "";
        }

        return std::string(buff.data(), r);
        #endif
        return "";
    }
}
