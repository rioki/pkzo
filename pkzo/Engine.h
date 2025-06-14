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

#pragma once
#include "config.h"

#include <filesystem>
#include <optional>
#include <string>

#include "Settings.h"

namespace pkzo
{
    //! Engine
    //!
    //! The engine class represents the central hub around which the engine
    //! runs.
    class PKZO_API Engine
    {
    public:
        //! Engine settings structure.
        struct Init
        {
            //! Engine Id
            //!
            //! The engine id is a unique id that is used to identify the engine.
            //! It will be used to resolve user folder and other system wide
            //! things. So make sure it really is unique.
            std::string id;

            //! Engine Version
            std::string version;
        };

        //! Contruct Engine
        Engine(Init init);

        //! Destruct Engine
        ~Engine();

        //! Get the engine id.
        const std::string& get_id() const;

        //! Get the engine verion.
        const std::string& get_version() const;

        //! Get the user folder.
        //!
        //! On windows this is %LOCALAPPDATA%\id
        //! Else it's %HOME/.id
        //!
        //! This is the location where the settings file will be located.
        const std::filesystem::path& get_user_folder() const;

        //! Settings
        //!
        //! @{
        Settings& get_settings();
        const Settings& get_settings() const;
        //! @}

        //! Main loop.
        void run();

    private:
        std::string id;
        std::string version;

        Settings settings;

        mutable std::optional<std::filesystem::path> user_folder;

        Engine(const Engine&) = delete;
        Engine& operator = (const Engine&) = delete;
    };
}
