// pkzo
// Copyright 2025 Sean Farrell
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

#include "pch.h"
#include "Engine.h"

namespace pkzo
{
    Engine::Engine(Init init)
    : id(std::move(init.id)), version(std::move(init.version))
    {
        SDL_assert(!id.empty());
        SDL_assert(!version.empty());

        auto settings_file = get_user_folder() / "settings.yml";
        if (std::filesystem::exists(settings_file))
        {
            settings.load(settings_file);
        }
    }

    Engine::~Engine() = default;

    const std::string& Engine::get_id() const
    {
        return id;
    }

    const std::string& Engine::get_version() const
    {
        return version;
    }

    std::optional<std::string> safe_getenv(const char* name)
    {
        auto value = std::getenv(name);
        if (value == nullptr)
        {
            return std::nullopt;
        }
        return value;
    }

    const std::filesystem::path& Engine::get_user_folder() const
    {
        if (user_folder)
        {
            return *user_folder;
        }

        #ifdef _WIN32
        PWSTR path = nullptr;
        auto hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &path);
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to get %LOCALAPPDATA%.");
        }
        user_folder = std::filesystem::path(path) / id;
        CoTaskMemFree(path);
        #else
        auto home = safe_getenv("HOME");
        if (!home)
        {
            throw std::runtime_error("Failed to get user folder.");
        }
        user_folder = std::filesystem::path(*home) / "." + id;
        #endif

        return *user_folder;
    }

    Settings& Engine::get_settings()
    {
        return settings;
    }

    const Settings& Engine::get_settings() const
    {
        return settings;
    }

    void Engine::run()
    {

    }
}
