// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "LabEngine.h"

#include <ice/GraphicSystem.h>
#include <ice/InputSystem.h>
#include <ice/Keyboard.h>

namespace lab
{
    std::filesystem::path get_config_folder()
    {
        PWSTR szPath = NULL;
        auto hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &szPath);
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to get %LOCALAPPDATA%.");
        }
        auto result = std::filesystem::path(szPath) / "ice/lab";
        CoTaskMemFree(szPath);
        return result;
    }

    LabEngine::LabEngine()
    {
        auto config_dir = get_config_folder();
        // create config dir in all cases
        std::filesystem::create_directories(config_dir);

        auto settings_file = config_dir / "settings.json";
        if (std::filesystem::exists(settings_file))
        {
            load_settings(settings_file);
        }

        start_system<ice::GraphicSystem>();
        start_system<ice::InputSystem>();

        auto* keyboard = get_keyboard();
        assert(keyboard);
        keyboard->on_key_up([this] (auto mod, auto key) {
            if (key == ice::Key::ESCAPE)
            {
                stop();
            }
        });
    }
}


