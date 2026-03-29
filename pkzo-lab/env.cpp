// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "env.h"

#include <pkzo/debug.h>

#include <cassert>
#include <array>

#ifdef _WIN32
#include <Windows.h>
#include <ShlObj.h>
#endif

#include <cstdlib>

using namespace std::string_literals;

namespace lab
{
    #ifndef _WIN32
    std::string safe_getenv(const std::string_view name)
    {
        if (name.empty())
        {
            throw std::invalid_argument("get_env_variable: empty name");
        }

        auto value = std::getenv(name.data());
        if (value == nullptr)
        {
            return {};
        }
        else
        {
            return value;
        }
    }
    #endif

    std::filesystem::path get_user_folder()
    {
        #ifdef _WIN32
        auto buff = std::array<wchar_t, MAX_PATH>{};
        auto hr   = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, buff.data());
        if (hr < 0)
        {
            throw std::logic_error("Could not determine APPDATA folder.");
        }
        return std::filesystem::path(buff.data()) / "pkzo" / "lab";
        #else
        return std::filesystem::path(safe_getenv("HOME")) / ".pkzo" / "lab";
        #endif
    }

    std::filesystem::path get_save_folder()
    {
        return get_user_folder() / "saves";
    }

    #ifdef _WIN32
    std::optional<std::wstring> get_registry_string(HKEY hKey, const std::wstring_view lpSubKey, const std::wstring_view lpValue)
    {
        auto flags = RRF_RT_REG_SZ | REG_EXPAND_SZ;
        auto bytes = DWORD{0u};
        auto r = RegGetValueW(hKey, lpSubKey.data(), lpValue.data(), flags, nullptr, nullptr, &bytes);
        if (r != ERROR_SUCCESS)
        {
            return std::nullopt;
        }

        // RegGetValueW guarantees string with null terminator.
        // If there is no data, it's not ERROR_SUCCESS
        assert(bytes > 0);
        // If there is data is must be N * sizeof(wchar_t)
        assert((bytes % sizeof(wchar_t)) == 0);

        auto buffer = std::vector<wchar_t>(bytes / sizeof(wchar_t), L'\0');
        r = RegGetValueW(hKey, lpSubKey.data(), lpValue.data(), flags, nullptr, reinterpret_cast<PVOID>(buffer.data()), &bytes);
        // We expect the registry to be stable while we run.
        // If something changed. the environment was tampered, so fail out hard.
        if (r != ERROR_SUCCESS)
        {
            throw std::runtime_error("Failed to read data from registry.");
        }

        return std::wstring(buffer.data(), buffer.size() - 1);
    }
    #endif

    std::filesystem::path get_asset_folder()
    {
        static auto asset_folder = std::filesystem::path();
        if (!asset_folder.empty())
        {
            return asset_folder;
        }

        if (pkzo::is_debugger_present())
        {
            static auto check_file = std::filesystem::path("assets/");
            if (std::filesystem::exists(check_file))
            {
                asset_folder = std::filesystem::canonical(check_file);
                return asset_folder;
            }
        }

        #ifdef _WIN32
        auto subKey = L"Software\\pkzo\\lab"s;
        auto value  = L"InstallFolder"s;
        auto path = get_registry_string(HKEY_CURRENT_USER, subKey.c_str(), value);
        if (!path.has_value())
        {
            path = get_registry_string(HKEY_LOCAL_MACHINE, subKey.c_str(), value);
            if (!path.has_value())
            {
                // we are neither in a dev environment, nor installed...
                throw std::runtime_error("Failed to get install folder.");
            }
        }
        // canonical will throw if the folder does not exist, so no need to check.
        asset_folder = std::filesystem::canonical(std::filesystem::path(*path) / "assets");
        #else
        asset_folder = std::filesystem::canonical(std::filesystem::path(safe_getenv("PKZO_LAB_BASE")) / "assets");
        #endif

        return asset_folder;
    }
}
